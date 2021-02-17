#ifndef ARMA_H_
#define ARMA_H_

// Tipo de estructura
struct arma_t;

// Para reservar espacio en memoria
struct arma_t* nuevaArma();

// Constructor
void inicializarArma(struct arma_t*, int);

// Destructor
void destruirArma(struct arma_t*);

// Operaciones
int hayBalas(struct arma_t*);
void dispararArma(struct arma_t*);
void recargarArma(struct arma_t*);
int armaSize(struct arma_t*);

#endif /* ARMA_H_ */