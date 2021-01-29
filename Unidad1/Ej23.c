//programa que encripta y desencripta un archivo pasando datos desde el main
//argv[1]:nombre archivo entrada, argv[2]=nombre archivo salida, argv[3]=funcion de encriptado

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//encriptado mediante xor
int encriptarXor(int data) { return data ^ 0xFF; }
//encriptado mediante not
int encriptarNot(int data) { return ~data; }

int main(int argc, char *argv[]) {

    char linea[50];
    //puntero a la funcion
    int (*pFuncionXor)(int); 
    int (*pFuncionNot)(int);
    int swFuncion=0;
    
    //abrir archivo para lectura
    FILE *archivoEntrada = fopen(argv[1], "r");
    if (archivoEntrada == NULL) {
        perror("Error: ");
        return EXIT_FAILURE;
    }

    if (strncmp("xor", argv[3], 3) == 0) {
        pFuncionXor= &encriptarXor;
        swFuncion=1;
    }
    else if(strncmp("not", argv[3], 3) == 0){
        pFuncionNot= &encriptarNot;
        swFuncion=2;
    }
    else{
        return EXIT_FAILURE;
    }


    //abrir archivo para escritura
    FILE *archivoSalida= fopen(argv[2], "w");
    if (archivoSalida == NULL) {
        perror("Error: ");
        return EXIT_FAILURE;
    }

    while (fgets(linea, sizeof(linea), archivoEntrada) != NULL) {
        
        int numCaracteres = strlen(linea);
        for (int i = 0; i < numCaracteres; i++) {
            //realiza operacion de encriptado
            if(swFuncion==1){
                linea[i] = (*pFuncionXor)(linea[i]);
            }
            else
            {
                linea[i] = (*pFuncionNot)(linea[i]);
            }   
        }
        //paso los datos encriptados al archivo de salida
        fputs(linea, archivoSalida);
    }

    //cerrar archivos
    fclose(archivoEntrada);
    fclose(archivoSalida);

    return EXIT_SUCCESS;
}