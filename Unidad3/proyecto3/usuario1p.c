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
#include <sys/wait.h>
#include <semaphore.h>

#define SH_SIZE1 200
#define SH_SIZE2 200
#define SNAME "sem1"

//prototipado de funciones
void *enviarMensaje(void*);
void *recibirMensaje(void*);
sem_t *sem1;
sem_t *sem2;

int main(void) {
   
    int fd;
    pthread_t hiloEnvia;
    pthread_t hiloRecibe;

    //crea memoria compartida
    int shm_fd1 = shm_open("MemoryObject1", O_CREAT | O_RDWR, 0600);
    if (shm_fd1 < 0) {
         perror("shm memory error: ");
         exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Shared memory is created with fd: %d\n", shm_fd1);

    if (ftruncate(shm_fd1, SH_SIZE1 * sizeof(char)) < 0) {
        perror("Truncation failed: ");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "The memory region is truncated.\n");

    //abre memoria 2
    int shm_fd2 = shm_open("MemoryObject2", O_RDONLY, 0600);
     if (shm_fd2 < 0) {
         perror("shm memory error: ");
         exit(EXIT_FAILURE);
     }
     fprintf(stdout, "Shared memory is created with fd: %d\n", shm_fd2);


    pthread_create(&hiloEnvia, NULL, &enviarMensaje, shm_fd1);
    pthread_create(&hiloRecibe, NULL, &recibirMensaje, shm_fd2);
    
    pthread_join(hiloEnvia,NULL);
    pthread_join(hiloRecibe, NULL);

   return 0;
}

void *enviarMensaje(void *shm_fd){
    int fd;
    int len;
    char buf[40];
    char* p;
    void* map;

    printf("Estado: listo para enviar o recibir mensajes.\n");
    printf("Ingrese un mensaje, escriba ^D para terminar:\n");

    while(fgets(buf, sizeof buf, stdin) != NULL){

        len = strlen(buf);
        if (buf[len-1] == '\n') buf[len-1] = '\0';

        map = mmap(NULL, SH_SIZE1, PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if (map == MAP_FAILED) {
            perror("Mapping failed: ");
            exit(EXIT_FAILURE);
        }
        p= (char*)map;
        strcpy(p,buf);
        printf("P=%s",p);
    }

    fprintf(stdout, "Data is written to the shared memory.\n");

    if (munmap(p, SH_SIZE1) < 0) {
         perror("Unmapping failed: ");
         exit(EXIT_FAILURE);
     }


     if (close(shm_fd) < 0) {
         perror("Closing shm failed: ");
         exit(EXIT_FAILURE);
     }

     if (shm_unlink("MemoryObject1") < 0) {
         perror("Unlink failed: ");
         exit(EXIT_FAILURE);
     }

    return 0;

}
void *recibirMensaje(void *shm_fd){
    int fd;
    char *p;

    for(;;) { 

        void* map = mmap(NULL, SH_SIZE2, PROT_READ, MAP_SHARED, shm_fd, 0);
        if (map == MAP_FAILED) {
            perror("Mapping failed: ");
            exit(EXIT_FAILURE);
        }
        p = (char*)map;

        fprintf(stdout, "The contents of shared memory object: %s\n", p);

        if (munmap(p, SH_SIZE2) < 0) {
            perror("Unmapping failed: ");
            exit(EXIT_FAILURE);
        }
        
    } 

    printf("Los mensajes han finalizado.\n");

    return 0;
}