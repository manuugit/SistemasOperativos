//programa que copia el contenido de un archivo1 a un archivo2
#include <stdio.h>
#include <stdlib.h>

char archivoE[50] = "/home/manuela/Escritorio/archivo1.txt";
char archivoS[50] = "/home/manuela/Escritorio/archivo2.txt";

int main(void){
    FILE *ar1; //archivo entrada
    FILE *ar2; //archivo salida
    int caracter;
    //abrir archivo para lectura
    ar1 = fopen(archivoE,"r");
    //valida que no sea nulo
    if(ar1 == NULL){
        printf("No se pudo abrir archivo \n%s", archivoE);
        exit(EXIT_FAILURE);
    }
    //abro archivo para escritura
    ar2 = fopen(archivoS,"w");
    //recorrer
    while(!feof (ar1)){
        caracter = fgetc(ar1);
        fputc(caracter,ar2); //pasar datos a archivo2
        //revisar si ya el archivo terminó
        if (caracter == EOF){
            break;
        }
    }
    //cerrar archivos
    fclose(ar1);
    fclose(ar2);
    printf("Se escribió correctamente\n");
}
