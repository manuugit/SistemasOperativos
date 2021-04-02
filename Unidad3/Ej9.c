/*comunicacion bidireccional  entre proceso padre e hijo. 
El proceso padre debe enviar al hijo el contenido de la cadena “mensaje_desde_el_padre” y el proceso hijo el contenido de la cadena “mensaje_desde_el_hijo”. 
(cadenas pasadas desde linea de comandos)*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
 {
     int fd1[2]; //dir padre hijo
     int fd2[2]; //dir hijo padre
     pid_t idp;
     char msj1[strlen(argv[1])];
     char msj2[strlen(argv[2])];
    
    //creacion de pipes
    pipe(fd1);
    pipe(fd2);

    idp=fork();
    switch(idp){
        case -1: /* Error */
        printf("Error al crear el proceso");
        return -1;

        case 0: /*proceso hijo*/
        //recibe cadena del padre /*direccion padre hijo*/
        close(fd1[1]); //cierra descriptor de escritura
        read(fd1[0],msj1,sizeof(msj1));
        printf("Hijo leyó: %s\n",msj1);
        close(fd1[0]);

        /*direccion hijo padre*/
        close(fd2[0]); //cierra descriptor de lectura
        write(fd2[1],argv[2],strlen(argv[2]));
        close(fd2[1]);

        break;

        default: /*proceso padre*/
        //envia cadena al hijo /*direccion padre hijo*/
        close(fd1[0]); //cierra descriptor de lectura
        write(fd1[1],argv[1],strlen(argv[1]));
        close(fd1[1]);

        /*direccion hijo padre*/
        close(fd2[1]); //cierra descriptor de escritura
        read(fd2[0],msj2,sizeof(msj2));
        printf("Padre leyó: %s \n",msj2);
        close(fd2[0]);

        wait(NULL); /* Wait for child to finish */
        break;
    }


 }