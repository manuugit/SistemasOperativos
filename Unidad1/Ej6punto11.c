//programa para calcular el promedio de los valores de un arreglo de 100 posiciones
#include <stdio.h>

int vector[100];
int i=0;
float promedio;
float calculaPromedio(int [100]); //prototipar funcion
int main(void){

    printf("Vector :");
    for(i=0; i<100; i++){ //se llena el vector
        vector[i] = i;
        printf(" %d ",vector[i]);
        if(i==99){
            printf("\n");
        }
    }
    //se llama la funcion del promedio y se imprime
    printf("Promedio=%.3f\n",calculaPromedio(vector));

return(0);
}

float calculaPromedio(int vector[100]){
    for (i=0; i<100; i++){
        promedio = promedio + vector[i];
    }
    promedio = promedio/100;
    return promedio;
}