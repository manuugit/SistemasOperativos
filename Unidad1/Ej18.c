//programa que permite imprimir un arreglo e insertar nuevos elementos dando la posición deseada
#include <stdio.h>

void imprimirArreglo(int longitud, int *arr);
int main(void){
    int arr[100];
    int posicion;
    int longitud;
    int nuevo;

    printf("Escriba el tamaño del arreglo\n");
    scanf("%d", &longitud);
    for(int i=0; i<longitud; i++){
        printf("Escriba el numero para la posicion %d\n",(i+1));
        scanf("%d", &(arr[i]));
    }

    imprimirArreglo(longitud, arr);

    printf("Escriba la posicion donde desea insertar un nuevo elemento y seguido de un espacio escriba el nuevo elemento\n");
    scanf("%d %d",&posicion, &nuevo);
    posicion = posicion-1;
    longitud = longitud +1;
    
    for(int i=longitud-1; i>=(posicion); i--){
        arr[i] = arr[i-1]; 
    }
    arr[posicion] = nuevo;
    
    imprimirArreglo(longitud, arr);
}
void imprimirArreglo(int longitud, int *arr)
{
    printf("Arreglo:\n");
    for(int i=0; i<longitud; i++){
        printf("[%d]: %d\n",(i+1),*(arr+i));
    }
}