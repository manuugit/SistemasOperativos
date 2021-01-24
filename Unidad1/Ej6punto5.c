//estructura de datos, imprimir sus miembros
#include <stdio.h>

int main(void){
    //declaracion de la estructura
    struct cdsMusica
    {
        char titulo[40];
        char artista[40];
        char genero[15];
        int numCanciones;
        int lanzamiento;
        int precio;
    };

    //inicialización variable
    struct cdsMusica cd1 = {"Brindo con el alma", "Diomedez Diaz", "Vallenato", 11, 1986,19900};
    //salida
    printf(" Titulo: %s\n Artista: %s\n Genero: %s\n Num de canciones: %d\n Año de lanzamiento: %d\n Precio: $ %d\n", cd1.titulo,cd1.artista,cd1.genero,cd1.numCanciones,cd1.lanzamiento,cd1.precio );
    return(0);
}