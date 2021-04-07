//solucion a la condicion de carrera en el programa, usando mutex (sincronizacion de hilos con exclusion mutua)
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS 100
#define LOOPS 1000000

pthread_mutex_t sum_mutex; // declaracion de la variable para usar el mutex
long sum = 0;

void  *doWork(void *pdata){
    long i;

    for(i= 0; i<LOOPS;i++){
        // 3. Entrar a la región crítica
        pthread_mutex_lock(&sum_mutex); //en la funcion que realiza el hilo, bloqueo
        sum = sum + 1;
        // 4.  Salir de la región crítica
        pthread_mutex_unlock(&sum_mutex); //desbloqueo
    } 
    pthread_exit(NULL);
}

int main(int argc, char * argv[]){
    pthread_t threads[NTHREADS];
  
    // Inicializar el mutex
    pthread_mutex_init(&sum_mutex,NULL);

    for(int i = 0;i<NTHREADS;i++){
        pthread_create(&threads[i],NULL,doWork,NULL);
    }

    for(int i = 0;i<NTHREADS;i++){
        pthread_join(threads[i],NULL);
    }
    
    //ya dejamos de usar el semaforo, entonces se destruye
    pthread_mutex_destroy(&sum_mutex);
    
    printf("Thread sum: %ld\n",sum);
    sum = 0;
    for(int i = 0; i<NTHREADS*LOOPS;i++){
        sum = sum +1;
    }
    printf("Check sum : %ld\n",sum);

    pthread_exit(NULL);
}

