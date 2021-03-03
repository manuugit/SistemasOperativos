//programa que calcula el minimo de n argumentos enteros pasados desde línea de comandos

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int numeros[argc-1];
    int min=1000000;

    for (int i=1; i<argc; i++){
        //almacena argumentos en un arreglo de enteros
        numeros[i-1] = atoi(argv[i]);
        //calculo minimo
        if (atoi(argv[i])<min){
            min = atoi(argv[i]);
        }
    }

    //muestro resultados
    printf("%s %d\n", "Mínimo=", min);

 }