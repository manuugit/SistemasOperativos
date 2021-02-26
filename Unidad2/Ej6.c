//crear 3 procesos un padre y 2 hijos, donde los hijos calculan el factorial del 1 al 10
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

 int main(int argc, char *argv[]) {
     __pid_t pid_hijo;
     int factorial=1;
     printf("El pid del programa padre es: %d\n",(int)getpid());
     for (int i=0; i<2;i++){
        factorial=1;
        pid_hijo = fork();
        if(pid_hijo==0){
            printf("%s %d %s %d\n","\nPROCESO HIJO",(i+1), "con pid",(int)getpid());
            break;
        }
        
     }
        switch(pid_hijo) {
            case -1: /* Error */
                printf("Error al crear el proceso");
                return -1;
            case 0: /* Código ejecutado por el hijo */
                for(int j=1; j<=10; j++){
                    factorial = factorial*j;
                    printf("%s %d %s %d\n", "fact(",j,")=",factorial);
                }
            break;
            default: /* Código ejecutado por el padre */
                wait(NULL);
                wait(NULL);

        }
        // ejecutada por todos los procesos
        printf("Proceso %d terminando \n",(int)getpid());
        
     
     exit(EXIT_SUCCESS);
 }