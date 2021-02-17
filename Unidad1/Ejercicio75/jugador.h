#ifndef JUGADOR_H_
#define JUGADOR_H_

     // Tipos de datos
     struct jugador_t;
     struct arma_t;

     // Para reservar memoria
     struct jugador_t* construirJugador();

     // Constructor
     void inicializarJugador(struct jugador_t*, const char*);

     // Destructor
     void destruirJugador(struct jugador_t*);

     // Operaciones
     void elegirArma(struct jugador_t*, struct arma_t*);
     void dispararJ(struct jugador_t*);
     void soltarArma(struct jugador_t*);

#endif /* JUGADOR_H_ */