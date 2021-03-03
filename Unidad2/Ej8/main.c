#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


 int main(int argc, char *argv[]) {
     __pid_t pid_hijo;
     int idhijo;
     
     printf("El pid del programa padre es: %d\n",(int)getpid());
     for (int i=0; i<=2;i++){
        pid_hijo = fork();
        if(pid_hijo==0){
            //printf("%s %d %s %d\n","\nPROCESO HIJO",(i+1), "con pid",(int)getpid());
            idhijo = i;
            break;
        }
        
     }
        switch(pid_hijo) {
            case -1: /* Error */
                printf("Error al crear el proceso");
                return -1;
            case 0: /* Código ejecutado por el hijo */
               if (idhijo== 0){
                   //printf("hijo1 %d\n",(int)getpid());
                   execvp("./exePromedio",argv);
                   
               }
               else if(idhijo==1){
                   //printf("hijo2 %d\n",(int)getpid());
                   execv("./exeMin",argv);
                   
               }
               else if(idhijo==2){
                   //printf("hijo3 %d\n",(int)getpid());
                   execvp("./exeMax",argv);
                   
               }
            break;
            default: /* Código ejecutado por el padre */
                wait(NULL);
                wait(NULL);
                wait(NULL);

        }
        // ejecutada por todos los procesos
        printf("Proceso %d terminando \n",(int)getpid());
        
     
     exit(EXIT_SUCCESS);
 }