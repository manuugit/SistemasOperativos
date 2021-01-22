#include <stdio.h>

int main(void)
{
    float op1;
    float op2;
    int operacion;
    char sig= 's';

    while(sig!='q'){
        printf("Ingrese el 1er operando\n");
        scanf("%f",&op1);
        printf("Ingrese el 2do operando\n");
        scanf("%f",&op2);
        printf("Escriba 1 para sumar, 2 para restar, 3 para multiplicar\n");
        scanf("%d", &operacion);
        if(operacion== 1)
            printf("%.3f + %.3f = %.3f\n",op1,op2,op1+op2);

        else if(operacion == 2)
            printf("%.3f - %.3f = %.3f\n",op1,op2,op1-op2);
        else if(operacion==3)
            printf("%.3f * %.3f = %.3f\n",op1,op2,op1*op2);
        else {
            printf("opcion no valida\n");
            return(0);}

        printf("Si desea continuar escriba s si no escriba q\n");
        scanf("\n%c",&sig);
    }
    
    return(0);
}