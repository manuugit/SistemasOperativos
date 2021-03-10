//lee un archivo de entrada que organiza la info en una estructura de datos
//cada línea del archivo tiene 3 cadenas de caracteres separados por espacios: nombre ocupación edad

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

//estructuras de datos
typedef struct linea{
    char nombre[20];
    char ocupacion[20];
    int edad;
} linea_t;

typedef struct archivoC{
    linea_t *plinea;
    int cantidadlineas;
} archivoC_t;

archivoC_t archivoComp;
archivoC_t *parchivoComp =&archivoComp;
FILE *archivoEntrada;

//prototipado de funciones
void *ordenarInverso(void*);
void *ordenarAlfabeticamente(void*);

int main(void){
    char nombreA1 [50] = "archivoEp2.txt";
    int contlinea = 0;
    char linea1 [63];
    int errorCondiciones=0;
    char nombreT[20];
    char ocupacionT[20];
    int edadT;

    pthread_t hilo1;
    pthread_t hilo2;

    //abrir archivo para lectura
    archivoEntrada = fopen(nombreA1, "r");
    if (archivoEntrada == NULL) {
        perror("Error: ");
        return EXIT_FAILURE;
    }

    while (fgets(linea1, sizeof(linea1), archivoEntrada) != NULL) {
        contlinea++;
        if (contlinea >100){
            errorCondiciones=1;
            break;
        }
    }
    
    fclose(archivoEntrada);

    if(errorCondiciones==0){
        archivoEntrada = fopen(nombreA1, "r");
        archivoComp.cantidadlineas = contlinea;
        //printf("#lineas %d\n",archivoComp.cantidadlineas);
        parchivoComp->plinea= (linea_t *)malloc(sizeof(linea_t)*archivoComp.cantidadlineas);
        contlinea = 0;

        //se carga la estructura de datos desde el archivo
        while (fscanf(archivoEntrada, "%s %s %d", nombreT, ocupacionT, &edadT) != EOF){
            strcpy((archivoComp.plinea+contlinea)->nombre, nombreT);
            strcpy((archivoComp.plinea+contlinea)->ocupacion, ocupacionT);
            (archivoComp.plinea+contlinea)->edad = edadT;
            contlinea++; 
        }

        //se imprime en pantalla desde la estructura de datos
        for (int i=0; i<archivoComp.cantidadlineas;i++){
            printf("%s %s %d\n",(archivoComp.plinea+i)->nombre, (archivoComp.plinea+i)->ocupacion, (archivoComp.plinea+i)->edad);

        }
    }

    else{
        printf("El archivo supera las 100 líneas, no cumple las condiciones\n");
    }
    
    fclose(archivoEntrada);

    pthread_create(&hilo1, NULL, &ordenarInverso, "archivoEp2.txt");
    pthread_create(&hilo2, NULL, &ordenarAlfabeticamente, "archivoEp2.txt");
    pthread_join(hilo1,NULL);
    pthread_join(hilo2, NULL);
    return 0;
}

void *ordenarInverso(void *archivo){
    archivoEntrada = fopen(archivo, "r");
    //archivo para escritura
    FILE *archivoSalida= fopen("salida1.txt", "w");
    for (int i=archivoComp.cantidadlineas; i>=0;i--){
            fprintf(archivoSalida, "%s %s %d\n",(archivoComp.plinea+i)->nombre, (archivoComp.plinea+i)->ocupacion, (archivoComp.plinea+i)->edad);
        }

    fclose(archivoEntrada);
    fclose(archivoSalida);

    return 0;
}

void *ordenarAlfabeticamente(void *archivo){

    return 0;
}