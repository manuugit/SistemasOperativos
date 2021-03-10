//programa para crear 2 procesos que ejecutan los programas de p1 y p2
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


 int main(int argc, char *argv[]) {
     __pid_t pid_hijo;
     int idhijo;
     
     printf("El pid del programa padre es: %d\n",(int)getpid());
     for (int i=0; i<2;i++){
        pid_hijo = fork(); //crea el proceso
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
                   execvp("./exep1",argv);
                   
               }
               else if(idhijo==1){
                   //printf("hijo2 %d\n",(int)getpid());
                   execv("./exep2",argv);
                   
               }
            break;
            default: /* Código ejecutado por el padre */
                wait(NULL);
                wait(NULL);
                
                char linea[32];
                //abre archivos para lectura
                FILE *archivo1 = fopen(argv[2], "r");
                if (archivo1 == NULL) {
                    perror("Error: ");
                    return EXIT_FAILURE;
                }
                FILE *archivo2 = fopen(argv[3], "r");
                if (archivo2 == NULL) {
                    perror("Error: ");
                    return EXIT_FAILURE;
                }

                printf("Archivo 1\n");
                while (fgets(linea, sizeof(linea), archivo1) != NULL) {
                    printf("%s",linea);
                }
                printf("Archivo 2\n");
                while (fgets(linea, sizeof(linea), archivo2) != NULL) {
                    printf("%s",linea);
                }

        }
       
        printf("Proceso %d terminando \n",(int)getpid());
        
     
     exit(EXIT_SUCCESS);
 }