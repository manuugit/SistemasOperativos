//analizar funcionamiento del programa (retorno de scanf)
//se completa el codigo para correccion
#include <stdio.h>

int main(void)
{
    int a;
    char residuo[10];
    printf("enter a number: ");
    while (scanf("%d", &a) != 1)
    {
        // input was not a number, ask again:
        scanf("%s",&residuo); //sacar del flujo de entrada la cadena que no ha sido convertida
        printf("enter a number:");
    }
    printf("You entered %d.\n", a);
}