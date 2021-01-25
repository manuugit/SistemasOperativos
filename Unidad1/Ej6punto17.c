//programa usando funciones fscanf, fprintf, fgets, fputs
//lee numeros (por linea) desde un archivo, calcula la suma y la escribe
#include <stdio.h>
#include <stdlib.h>

char nombreArchivo [50] = "/home/manuela/Escritorio/archivo2.txt";
int main(void){
    FILE *archivo; //declara archivo
    char datos[10];
    int suma;
    //abrir archivo para lectura
    archivo = fopen(nombreArchivo,"r");
    //valida que no sea nulo
    if(archivo== NULL){
        printf("No se pudo abrir archivo \n%s", nombreArchivo);
        exit(EXIT_FAILURE);
    }
    //recorrer
    while(fgets(datos,10,archivo)){ //lee cada linea
        suma = suma + atoi(datos); //acumula y castea cadena a entero
    }
    fprintf(archivo, "%d\n", suma);
    fscanf(archivo, "%d", &suma);
    fclose(archivo);  //cerrar archivo
    //abrir archivo para escritura
    archivo = fopen(nombreArchivo,"w");
    fprintf(archivo,"Suma de los numeros= %d\n ", suma); //escribe el valor de la suma en el archivo
    fputs("suma realizada con exito\n",archivo);
    //cerrar archivo
    fclose(archivo);
    printf("%s","Se procesó y escribió archivo");
    return 0;
}
