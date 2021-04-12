//El proceso padre debe enviar al hijo el mensaje recibido por la entrada estandar en minuscula. 
//el hijo recibe el mensaje y lo pasa a mayuscula, para luego devolverlo al padre
//el padre finalmente muestra el mensaje recibido por la salida estandar

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
     int fd1[2]; //dir padre hijo
     int fd2[2]; //dir hijo padre
     pid_t idp;
     char cadena[40];

    //creacion de pipes
    pipe(fd1);
    pipe(fd2);

    idp=fork();
    if(idp == 1){ /* Error */
        printf("Error al crear el proceso");
        return -1;
    }
    if(idp == 0){ 
        /*proceso hijo*/
        //recibe cadena del padre /*direccion padre hijo*/

        close(fd1[1]); //cierra descriptor de escritura pipe 1
        close(fd2[0]); //cierra descriptor de lectura pipe 2

        for(;;) {
           
            read(fd1[0],cadena,40);
            printf("Hijo leyó: %s\n",cadena);
            

            //convierte lo leido a mayuscula
            for(int i=0; i<40; i++){
                cadena[i] = toupper(cadena[i]);
            }
            

            /*direccion hijo padre*/
            write(fd2[1],cadena,40); //escribe en el pipe 2
            printf("Hijo envia: %s\n",cadena);
        }
        close(fd1[0]);
        close(fd2[1]);

    }
    else{
        /*proceso padre*/
        //envia cadena al hijo /*direccion padre hijo*/

        close(fd1[0]); //cierra descriptor de lectura pipe 1
        close(fd2[1]); //cierra descriptor de escritura pipe 2

        for(;;) {
            printf("Escriba la cadena\n");
            scanf("%s",cadena);
            for(int i=0; i<40; i++){
                cadena[i] = tolower(cadena[i]);
            }
           
            write(fd1[1],cadena,40); //escribe en el pipe 1
            printf("Padre envia: %s\n",cadena);
            

            /*direccion hijo padre, padre recibe mensaje del hijo*/
            read(fd2[0],cadena,40);
            printf("Padre leyó MENSAJE FINAL: %s \n",cadena);
           
        }
        close(fd1[1]);
        close(fd2[0]);

    }
 
 }