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
        printf("Archivo original\n");
        for (int i=0; i<archivoComp.cantidadlineas;i++){
            printf("%s %s %d\n",(archivoComp.plinea+i)->nombre, (archivoComp.plinea+i)->ocupacion, (archivoComp.plinea+i)->edad);

        }
    }

    else{
        printf("El archivo supera las 100 líneas, no cumple las condiciones\n");
    }
    
    fclose(archivoEntrada);

    pthread_create(&hilo1, NULL, &ordenarInverso, "salida1.txt");
    pthread_create(&hilo2, NULL, &ordenarAlfabeticamente, "salida2.txt");
    pthread_join(hilo1,NULL);
    pthread_join(hilo2, NULL);
    return 0;
}

void *ordenarInverso(void *archivo){
    //archivo para escritura
    FILE *archivoSalida= fopen(archivo, "w");
    for (int i=archivoComp.cantidadlineas-1; i>=0;i--){
            fprintf(archivoSalida, "%s %s %d\n",(archivoComp.plinea+i)->nombre, (archivoComp.plinea+i)->ocupacion, (archivoComp.plinea+i)->edad);
        }

    fclose(archivoSalida);

    return 0;
}

void *ordenarAlfabeticamente(void *archivo){
    //archivo para escritura
    FILE *archivoSalida= fopen(archivo, "w");
    //vectores auxiliares
    char ocupaciones[archivoComp.cantidadlineas][20];
    char ocupacionesO[archivoComp.cantidadlineas][20];
    char min [20] =  "zz";
    int pos;
    int control=0;

    for(int i=0; i<archivoComp.cantidadlineas; i++){
        strcpy(ocupaciones[i],(archivoComp.plinea+i)->ocupacion);
    }

    for (int i=0; i<archivoComp.cantidadlineas; i++){
        //calculo la palabra menor
        for(int j=0; j<archivoComp.cantidadlineas;j++){
            if (strcmp(ocupaciones[j], min) <0){
                strcpy(min, ocupaciones[j]); //guardo la palabra menor
                pos = j;
            }   
        }
        strcpy(ocupaciones[pos],"zz"); //elimino la palabra menor actual
        strcpy(ocupacionesO[i],min); //guardo la palabra minima
        strcpy(min,"zz");
    }
    
    //guardo en el archivo de salida, en el orden correspondiente
    for (int i=0; i<archivoComp.cantidadlineas;i++){
        for(int j=0; j<archivoComp.cantidadlineas;j++){
            if (strcmp(ocupacionesO[i],(archivoComp.plinea+j)->ocupacion)==0){
                fprintf(archivoSalida,"%s %s %d\n",(archivoComp.plinea+j)->nombre, (archivoComp.plinea+j)->ocupacion, (archivoComp.plinea+j)->edad);
                control++;
                 if(control ==archivoComp.cantidadlineas ){
                     break;
                 }
                break;
            }

        if(control ==archivoComp.cantidadlineas ){
            break;
        }
        }   
    }

    fclose(archivoSalida);
    return 0;
}