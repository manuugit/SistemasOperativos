//programa que calcula el maximo de n argumentos enteros pasados desde línea de comandos

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int numeros[argc-1];
    int max=0;

    for (int i=1; i<argc; i++){
        //almacena argumentos en un arreglo de enteros
        numeros[i-1] = atoi(argv[i]); 
        //calculo maximo
        if (atoi(argv[i])>max){
            max = atoi(argv[i]);
        }
    }

    //muestro resultados
    printf("%s %d\n","Máximo",max);
  
 }