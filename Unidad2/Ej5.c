//calcular promedio, minimo y maximo de n argumentos pasados por linea de comandos
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    float suma=0;
    int numeros[argc-1];
    int max=0;
    int min=1000000;
    float promedio;

    for (int i=1; i<argc; i++){
        //almacena argumentos en un arreglo de enteros
        numeros[i-1] = atoi(argv[i]);
        suma = suma + atoi(argv[i]);
        //calculo maximo
        if (atoi(argv[i])>max){
            max = atoi(argv[i]);
        }
        //calculo minimo
        if (atoi(argv[i])<min){
            min = atoi(argv[i]);
        }
    }

    //calculo promedio
    promedio = suma / (argc-1);
    //muestro resultados
    printf("%-9s|%-9s|%-9s|\n", "Promedio", "Mínimo", "Máximo");
    printf("%-9.3f|%-8d|%-9d|\n", promedio, min, max);

 }