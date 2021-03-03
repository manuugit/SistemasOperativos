//programa que lee un archivo donde cada linea corresponde a una pareja clave valor, ordena las parejas por valor de mayor a menor y las escribe en un archivo de salida
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char nombreA1 [50] = "archivop1.txt";
    char nombreA2 [50] = "salidap1.txt";
    char clave[20];
    int valor;
    int valores[100]; //max 100
    char claves[100][20]; //max 100 claves de max 20 caracteres
    int contlinea=0;
    int max=-1000;
    char claveMax[20];
    int pos;

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

    //vectores para almacenar las parejas ordenadas
    int valoresO[contlinea];
    char clavesO[contlinea][20];

    for (int i=0; i<contlinea; i++){
        
        //calculo el mayor valor en el vector de valores
        for(int j=0; j<contlinea;j++){
            if (valores[j]> max){
                max= valores[j]; //guardo el valor maximo
                pos = j;
                strcpy(claveMax,claves[j]); //guardo la clave del valor maximo
            }   
        }
        
        valores[pos]=-1000; //elimino el mayor actual
        valoresO[i] = max; 
        strcpy(clavesO[i],claveMax);
        max = -1000;
    }

    //pasar información al archivo de salida
    
    fprintf(archivoSalida,"Parejas ordenadas de mayor a menor (clave valor)\n");
    for(int i=0; i<contlinea; i++){
        fprintf(archivoSalida,"%s %d\n",clavesO[i],valoresO[i]);
    }

    printf("Las parejas ordenadas de mayor a menor se escribieron en el archivo de salida\n");
    
    //cerrar archivos
    fclose(archivoEntrada);
    fclose(archivoSalida);

    return EXIT_SUCCESS;
}