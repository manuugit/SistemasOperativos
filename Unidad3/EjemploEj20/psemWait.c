//programa que espera
#include <stdio.h>
#include <stdlib.h>

#include <semaphore.h> //for semaphores
#include <fcntl.h>     //for 0_* constants
#include <sys/stat.h>  //for mode constants
#include <unistd.h>

int main(int argc, char *argv[]){

    //Note que ya no especifico el modo ni el valor
    sem_t *sem = sem_open("semExample",0);

    if(sem == SEM_FAILED){
        perror("pSemWait sem open: ");
        exit(EXIT_FAILURE);
    }

    printf("pSemWait %d sem_wait() ...\n", getpid());
    if(sem_wait(sem) == -1){
        perror("pSemWait sem_wait error: ");
        exit(EXIT_FAILURE);
    }
    printf("pSemWait %d suceeded\n", getpid());

    if(sem_close(sem) == -1){
        perror("pSemWait sem_close fails: ");
        exit(EXIT_FAILURE);
    }

    if(sem_unlink("semExample") == -1){
        perror("pSemWait sem_unlink falls: ");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}