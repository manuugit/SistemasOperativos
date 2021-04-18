#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>       //for semaphores
#include <sys/wait.h>

#define SH_SIZE1 200
#define SH_SIZE2 200

//prototipado de funciones
void *enviarMensaje(void*);
void *recibirMensaje(void*);

sem_t *sem1w, *sem1r;
sem_t *sem2w, *sem2r;

int main(void) {
   
    int shm_fd2;
    int shm_fd1;
    pthread_t hiloEnvia;
    pthread_t hiloRecibe;

    //crear semaforos
    mode_t perms = 0666;
    int flags = O_CREAT;
    unsigned int value = 0; //inicia cerrado

    sem2w = sem_open("sem2w", flags, perms, value);
    if(sem2w == SEM_FAILED){
        perror("user 2 sem_open sem2w fails: ");
        exit(EXIT_FAILURE);
    }

    sem2r = sem_open("sem2r", flags, perms, value);
    if(sem2r == SEM_FAILED){
        perror("user 2 sem_open sem2r fails: ");
        exit(EXIT_FAILURE);
    }

    //abrir semaforos del proceso 1
    sem1w = sem_open("sem1w",0);
    if(sem1w == SEM_FAILED){
        perror("user2 sem_open sem1w: ");
        exit(EXIT_FAILURE);
    }

    sem1r = sem_open("sem1r",0);
    if(sem1r == SEM_FAILED){
        perror("user2 sem_open sem1r: ");
        exit(EXIT_FAILURE);
    }

    //crea memoria compartida
    shm_fd2 = shm_open("MemoryObject2", O_CREAT | O_RDWR, 0600);
    if (shm_fd2 < 0) {
         perror("shm2 memory error: ");
         exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Shared memory is created with fd: %d\n", shm_fd2);

    if (ftruncate(shm_fd2, SH_SIZE2 * sizeof(char)) < 0) {
        perror("Truncation failed shm2: ");
        exit(EXIT_FAILURE);
    }

    //abre memoria 1
    shm_fd1 = shm_open("MemoryObject1", O_RDONLY, 0600);
    if (shm_fd1 < 0) {
        perror("shm1  memory error: ");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Shared memory is created with fd: %d\n", shm_fd1);


    pthread_create(&hiloEnvia, NULL, &enviarMensaje, shm_fd2);
    pthread_create(&hiloRecibe, NULL, &recibirMensaje, shm_fd1);
    
    pthread_join(hiloEnvia,NULL);
    pthread_join(hiloRecibe, NULL);

   return 0;
}

void *enviarMensaje(void *shm_fd){
    int len;
    char buf[SH_SIZE2];
    char* p;
    void* map;

    printf("Estado: listo para enviar o recibir mensajes.\n");
    printf("Ingrese un mensaje, escriba ^C para terminar:\n");

    while(fgets(buf, sizeof buf, stdin) != NULL){

        len = strlen(buf);
        if (buf[len-1] == '\n') buf[len-1] = '\0';

        //abrir candado semaforo de escritura 2
        if(sem_post(sem2w) == -1){
            perror("sem_post error sem2w: ");
            exit(EXIT_FAILURE);
        }

        map = mmap(NULL, SH_SIZE2, PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if (map == MAP_FAILED) {
            perror("Mapping failed: ");
            exit(EXIT_FAILURE);
        }
        p= (char*)map;
        memcpy(p, buf, sizeof(buf));

        //desmapear
        if (munmap(p, SH_SIZE2) < 0) {
            perror("Unmapping failed: ");
            exit(EXIT_FAILURE);
        }

        //cerrar candado semaforo de lectura 1
        if(sem_wait(sem1r) == -1){
            perror("sem_wait error sem1r: ");
            exit(EXIT_FAILURE);
        } 

    }

    //cerrar semaforos
    if(sem_close(sem2w) == -1){
        perror("sem_close fails sem2w: ");
        exit(EXIT_FAILURE);
    }

    if(sem_unlink("sem2w") == -1){
        perror("sem_unlink falls sem2w: ");
        exit(EXIT_FAILURE);
    }

    if(sem_close(sem2r) == -1){
        perror("sem_close fails sem2r: ");
        exit(EXIT_FAILURE);
    }

    if(sem_unlink("sem2r") == -1){
        perror("sem_unlink falls sem2r: ");
        exit(EXIT_FAILURE);
    }

    //cerrar espacio de memoria
    if (close(shm_fd) < 0) {
        perror("Closing shm failed: ");
        exit(EXIT_FAILURE);
     }

    if (shm_unlink("MemoryObject2") < 0) {
        perror("Unlink failed: ");
        exit(EXIT_FAILURE);
    }

    return 0;

}
void *recibirMensaje(void *shm_fd){
    char *p;
    for(;;) { 

        //cerrar candado semaforo de escritura 1
        if(sem_wait(sem1w) == -1){
            perror("sem_wait error sem1w: ");
            exit(EXIT_FAILURE);
        } 

        void* map = mmap(NULL, SH_SIZE1, PROT_READ, MAP_SHARED, shm_fd, 0);
        if (map == MAP_FAILED) {
            perror("Mapping failed: ");
            exit(EXIT_FAILURE);
        }
        p = (char*)map;

        fprintf(stdout, "Usuario 1: %s\n", p);

        //desmapear
        if (munmap(p, SH_SIZE1) < 0) {
            perror("Unmapping failed: ");
            exit(EXIT_FAILURE);
        }

        //abrir candado semaforo de lectura 2
        if(sem_post(sem2r) == -1){
            perror("sem_post error sem2r: ");
            exit(EXIT_FAILURE);
        }
    } 

    printf("Los mensajes han finalizado.\n");

    return 0;
}