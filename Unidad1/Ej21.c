//programa que permite encontrar elementos comunes entre 2 arreglos
#include <stdio.h>
#include <stdint.h> //para que el compilador encuentre def de uint8_t

int main(void){
        uint8_t arrayCommon(int32_t* arr1, int32_t arr1Size,int32_t* arr2, int32_t arr2Size, int32_t* arrRes, int32_t arrResSize);
        int32_t arr1[100];
        int32_t arr2[100];
        int32_t longitud1;
        int32_t longitud2;
        int32_t arrRes[100];
        int32_t max=100;
        uint8_t comunes;

        //solicitar tamaño y elementos de los arreglos
        printf("Escriba el tamaño del arreglo 1 \n");
        scanf("%d", &longitud1);
        for(int i=0; i<longitud1; i++){
        printf("Escriba el numero para la posicion %d\n",(i+1));
        scanf("%d", &(arr1[i]));
        }

        printf("Escriba el tamaño del arreglo 2\n");
        scanf("%d", &longitud2);
        for(int i=0; i<longitud2; i++){
        printf("Escriba el numero para la posicion %d\n",(i+1));
        scanf("%d", &(arr2[i]));
        }

        printf("Vector resultado=");
        comunes=arrayCommon(arr1,longitud1,arr2,longitud2,arrRes, max);
        printf("Numero de elementos comunes=%d \n", comunes);
}
uint8_t arrayCommon(int32_t* arr1, int32_t arr1Size,int32_t* arr2, int32_t arr2Size, int32_t* arrRes, int32_t arrResSize){
 uint8_t cont=0;
 int repetido=0;
 for(int i=0; i<arr1Size; i++){
     for(int j=0; j<arr2Size; j++){
         if (arr1[i]== arr2[j]){
             for(int k=0; k< arrResSize; k++){
                 if (arrRes[k]==arr1[i]){
                     repetido=1;
                     k=arrResSize-1;
                 }
            }  
            if (repetido==0){
                arrRes[cont] = arr1[i];
                printf("%d ",arrRes[cont]);
                cont++;
            }       
        }
        repetido =0;
     }
 }
 printf("\n");
 return cont;
}