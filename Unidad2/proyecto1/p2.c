//programa que lee un archivo donde cada linea es una pareja clave valor, escribe las parejas en orden contrario en un archivo de salida
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char nombreA1 [50];
    char nombreA2 [50];
    char clave[20];
    int valor;
    int valores[100]; //max 100
    char claves[100][20]; //max 100 claves de max 20 caracteres
    int contlinea=0;
    
    //nombres de los archivos pasados como argumentos del main
    strcpy(nombreA1,argv[1]);
    strcpy(nombreA2,argv[3]);

    //abrir archivo para lectura
    FILE *archivoEntrada = fopen(nombreA1, "r");
    if (archivoEntrada == NULL) {
        perror("Error: ");
        return EXIT_FAILURE;
    }

    //abrir archivo para escritura
    FILE *archivoSalida= fopen(nombreA2, "w");
    if (archivoSalida == NULL) {
        perror("Error: ");
        return EXIT_FAILURE;
    }
    
    while (fscanf(archivoEntrada, "%s %d", clave, &valor) != EOF) {
        //printf("%s %d\n",clave, valor);
        contlinea++;
        strcpy(claves[contlinea-1],clave);
        valores[contlinea-1] = valor; 
    }

    //pasar información al archivo de salida
    
    fprintf(archivoSalida,"Parejas ordenadas en orden contrario al archivo de entrada (clave valor)\n");
    for(int i=(contlinea-1); i>=0; i--){
        fprintf(archivoSalida,"%s %d\n",claves[i],valores[i]);
    }

    printf("Las parejas se escribieron en orden contrario en el archivo de salida\n");
    
    //cerrar archivos
    fclose(archivoEntrada);
    fclose(archivoSalida);

    return EXIT_SUCCESS;
}