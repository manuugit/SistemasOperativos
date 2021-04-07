//arreglar una condicion de carrera en este programa
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

static long glob = 0;
pthread_mutex_t glob_mutex; // declaracion de la variable para usar el mutex

//funcion que va a ejecutar el hilo
static void* threadFunc(void *arg) {
    int loops = *((int *) arg);
    long loc;
    
    for (int j = 0; j < loops; j++) {
        // Entrar a la región crítica
        pthread_mutex_lock(&glob_mutex); //en la funcion que realiza el hilo, bloqueo
        loc = glob;
        loc++;
        glob = loc;
        // Salir de la región crítica
        pthread_mutex_unlock(&glob_mutex); //desbloqueo
       
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    pthread_t t1, t2;
    int loops, s;

    loops = (argc > 1) ? atol(argv[1]) : 10000000;
    printf("Valor de loops %d\n",loops);
    
    s = pthread_create(&t1, NULL, threadFunc, &loops);
    if (s != 0) perror("pthread create");

    glob=0;
    s = pthread_create(&t2, NULL, threadFunc, &loops);
    if (s != 0) perror("pthread create");

    //hilos lanzados paralelamente
    s = pthread_join(t1, NULL);
    //printf("Valor de glob hilo 1 %ld\n",glob);
    if (s != 0) perror("pthread_join");
   
    s = pthread_join(t2, NULL);
    //printf("Valor de glob hilo 2 %ld\n",glob);
    if (s != 0) perror("pthread_join");
   

    //ya dejamos de usar el semaforo, entonces se destruye
    pthread_mutex_destroy(&glob_mutex);

    printf("glob = %ld\n", glob);
    exit(EXIT_SUCCESS);
}