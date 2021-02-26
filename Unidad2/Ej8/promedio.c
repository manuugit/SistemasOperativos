//programa que calcula el promedio de n argumentos enteros pasados desde línea de comandos
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    float suma=0;
    int numeros[argc-1];
    float promedio;

    for (int i=1; i<argc; i++){
        //almacena argumentos en un arreglo de enteros
        numeros[i-1] = atoi(argv[i]);
        suma = suma + atoi(argv[i]);
    }

    //calculo promedio
    promedio = suma / (argc-1);
    //muestro resultados
    printf("%s %.3f\n", "Promedio=",promedio);

 }