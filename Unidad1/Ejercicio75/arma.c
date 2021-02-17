#include <stdlib.h>
#include <stdio.h>

// Definición de la estructura
typedef struct {
  int balas;
} arma_t;

// Reserva de memoria
arma_t* nuevaArma() {
  return (arma_t*)malloc(sizeof(arma_t));
}

// Constructor
void inicializarArma(arma_t* arma, int balasIniciales) {
  arma->balas= 0;
  if (balasIniciales > 0) {
    arma->balas = balasIniciales;
  }
}

// Destructor
void destruirArma(arma_t* arma) {
    free(arma);
}

// Operaciones
int hayBalas(arma_t* arma) {
    if(arma->balas > 0){
      return (1);
    }
    else return(0);
}

void dispararArma(arma_t* arma) {
  arma->balas = arma->balas -1;
  printf("Arma disparada\n");
}

void recargarArma(arma_t* arma) {
  arma->balas= 7;
  printf("Arma recargada\n");
}

int armaSize(arma_t* arma){
  return arma->balas;
}