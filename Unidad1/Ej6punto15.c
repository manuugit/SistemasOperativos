//programa que calcula el promedio ponderado de un estudiante
#include <stdio.h>
#include <stdlib.h>

int main(void){
    int numMaterias;
    char (*bufferM)[20];
    float *bufferC;
    float *bufferN;   
    int totalcreditos=0;
    float suma=0;

    printf("Ingrese numero de materias vistas en el semestre\n");
    scanf("%d",&numMaterias);
    //reserva de memoria
    bufferM = (char (*) [20])malloc(sizeof(char[20])*numMaterias);
    bufferC= (float *)malloc(sizeof(float)*numMaterias);
    bufferN = (float*)malloc(sizeof(float)*numMaterias);

    //pregunta por la informacion requerida y guarda datos en respectivo "buffer"
    for(int i=0; i<numMaterias;i++){
        printf("Ingrese nombre de la materia %d\n",i+1);
        scanf("%s",(char *)(bufferM+i));
        printf("Ingrese el numero de creditos\n");
        scanf("%f",(float *)(bufferC+i));
        printf("Escriba la nota obtenida\n");
        scanf("%f",(float *)(bufferN+i));

    }
    //datos quedaron guardados en buffer
    printf("|%-20.20s|%-4s|%-10s|\n","Materia","Nota","# creditos");
    suma=0;
    //hace los calculos
    for(int i=0; i<numMaterias;i++){
        printf("|%-20.20s|%-4.2lf|%-10.1f|\n", (char *)(bufferM+i),*(bufferN+i),*(bufferC+i));
        suma = suma +( (*(bufferN+i)) * (*(bufferC+i)));
        totalcreditos = totalcreditos + *(bufferC+i);
    }
    printf("Promedio ponderado:%.3f\n", (suma/totalcreditos));
    free(bufferM);
    free(bufferN);
    free(bufferC);
    
    return(0);
}

