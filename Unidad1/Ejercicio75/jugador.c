#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "arma.h"

// Definición de la estructura
typedef struct {
char* nombre;
struct arma_t* arma;
} jugador_t;

// Reserva de memoria
jugador_t* construirJugador() {
  return (jugador_t*)malloc(sizeof(jugador_t));
}

// Constructor
void inicializarJugador(jugador_t* jugador, const char* nombre) {
    jugador->nombre = (char*)malloc((strlen(nombre) + 1) * sizeof(char));
    strcpy(jugador->nombre, nombre);
    jugador->arma = NULL; //no ha elegido arma
}

// Destructor
void destruirJugador(jugador_t* jugador) {
  free (jugador);
}

// Operaciones
void elegirArma(jugador_t* jugador, struct arma_t* arma) {
  //elige arma, agregacion
  jugador->arma = arma;
}

void dispararJ(jugador_t* jugador) {
  if (jugador->arma != NULL)  {
    dispararArma(jugador->arma);
  }
  else {
    printf("El jugador no ha elegido arma\n");
  }
}

void soltarArma(jugador_t* jugador) {
  jugador->arma = NULL;
}