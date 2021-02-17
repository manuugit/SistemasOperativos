#include <stdio.h>
#include <stdlib.h>
#include "arma.h"
#include "jugador.h"

int main(int argc, char* argv[]) {
      
      // Objeto arma
      struct arma_t* arma1 = nuevaArma();
      inicializarArma(arma1, 7);

      // Objeto jugador
      struct jugador_t* jug = construirJugador();
      inicializarJugador(jug, "Camilo");

      //Prueba disparo sin haber elegido arma
      dispararJ(jug);
      // Agregar arma a jugador
      elegirArma(jug, arma1);
      // Ejecutar 3 disparos
      for(int i=0; i<3;i++){
            dispararJ(jug);
      }

      printf("%s %d\n","Cantidad de balas:",armaSize(arma1));
      // Recargar balas
      recargarArma(arma1);

      printf("%s %d\n","Cantidad de balas:",armaSize(arma1));
      // Ejecutar disparos
      while (hayBalas(arma1)==1) {
            dispararJ(jug);
      }

      printf("%s %d\n","Cantidad de balas:",armaSize(arma1));
      // Tirar arma, jugador queda sin arma
      soltarArma(jug);

      // Liberar
      destruirJugador(jug);
      destruirArma(arma1);

      return 0;
}