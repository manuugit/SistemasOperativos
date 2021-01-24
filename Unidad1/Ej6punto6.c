//programa que permite ingresar 2 puntos(x,y) y calcula el area del rectangulo
#include <stdio.h>
#include <stdlib.h>

int main(void){
    //declaracion estructura punto
    typedef struct punto{
        int x;
        int y;
    } point; //declara tipo variable
    //declaracion de los puntos
    point p1;
    point p2;

    //solicito informacion de los puntos
    printf("Escriba coordenada x del punto 1 \n");
    scanf("%d",&p1.x );
    printf("Escriba coordenada y del punto 1\n");
    scanf("%d",&p1.y);
    printf("Escriba coordenada x del punto 2\n");
    scanf("%d",&p2.x );
    printf("Escriba coordenada x del punto 2\n");
    scanf("%d",&p2.y );

    //calculo del area
    printf("Area del rectangulo=%d unidades cuadradas\n",abs(p2.x-p1.x)*1*abs(p2.y-p1.y));

    return(0);
}