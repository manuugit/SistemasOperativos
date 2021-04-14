/* Filename: msgq_send.c ENVIO DE MENSAJES A LA COLA*/ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

#define PERMS 0644
struct my_msgbuf {
   long mtype;
   char mtext[200];
};

//prototipado de funciones
void *enviarMensaje(void*);
void *recibirMensaje(void*);

int main(void) {
   
    int msqid1;
    key_t key1;

    int msqid2;
    key_t key2;
    system("touch cola1.txt");
    

    //cola para enviar (cola 1)
    if ((key1 = ftok("cola1.txt", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }
    
    if ((msqid1 = msgget(key1, PERMS | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }


    //cola para recibir (cola 2)
    if ((key2 = ftok("cola2.txt", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }
    
    if ((msqid2 = msgget(key2, PERMS)) == -1) { /* se conecta a la cola 2 */
        perror("msgget");
        exit(1);
    }

    pthread_t hiloEnvia;
    pthread_t hiloRecibe;


    printf("%d %d\n",msqid1,msqid2);

    pthread_create(&hiloEnvia, NULL, &enviarMensaje, msqid1);
    pthread_create(&hiloRecibe, NULL, &recibirMensaje, msqid2);
    
    pthread_join(hiloEnvia,NULL);
    pthread_join(hiloRecibe, NULL);

   return 0;
}

void *enviarMensaje(void *msqid){

    struct my_msgbuf buf;
    int len;
    printf("Estado: listo para enviar o recibir mensajes.\n");
    printf("Ingrese un mensaje, escriba ^D para terminar:\n");
    buf.mtype = 1; 
    
    while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL) {
        len = strlen(buf.mtext);
       
        if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';
        if (msgsnd(msqid, &buf, len+1, 0) == -1) 
        perror("msgsnd");
    }
    strcpy(buf.mtext, "fin");
    len = strlen(buf.mtext);
    if (msgsnd(msqid, &buf, len+1, 0) == -1) 
    perror("msgsnd");
    
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    return 0;

}
void *recibirMensaje(void *msqid){

    struct my_msgbuf buf;
    int toend;
    
    for(;;) { 
        if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        printf("Usuario2: \"%s\"\n", buf.mtext);
        toend = strcmp(buf.mtext,"fin");
        if (toend == 0)
        break;
    }
    printf("Los mensajes han finalizado.\n");
    system("rm cola2.txt");

    return 0;
}