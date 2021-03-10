//lee un archivo de entrada que organiza la info en una estructura de datos
//cada línea del archivo tiene 3 cadenas de caracteres separados por espacios: nombre ocupación edad

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

linea_t lineaA;
linea_t *plineaA= &lineaA;
archivoC_t archivoComp;
archivoC_t *parchivoComp =&archivoComp;

int main(void){
    char nombreA1 [50] = "archivoEp2.txt";
    int contlinea = 0;
    char linea1 [63];
    int errorCondiciones=0;
    char nombreT[20];
    char ocupacionT[20];
    int edadT;
    //abrir archivo para lectura
    FILE *archivoEntrada = fopen(nombreA1, "r");
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

        while (fscanf(archivoEntrada, "%s %s %d", nombreT, ocupacionT, &edadT) != EOF){
            strcpy((archivoComp.plinea+contlinea)->nombre, nombreT);
            strcpy((archivoComp.plinea+contlinea)->ocupacion, ocupacionT);
            (archivoComp.plinea+contlinea)->edad = edadT;
            contlinea++; 
        }

        for (int i=0; i<archivoComp.cantidadlineas;i++){
            printf("%s %s %d\n",(archivoComp.plinea+i)->nombre, (archivoComp.plinea+i)->ocupacion, (archivoComp.plinea+i)->edad);

        }
    }

    else{
        printf("El archivo supera las 100 líneas, no cumple las condiciones\n");
    }
    
    fclose(archivoEntrada);
    return 0;
}