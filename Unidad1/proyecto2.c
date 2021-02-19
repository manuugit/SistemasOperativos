//nueva versión del proyecto1, permite manejar varias bases de datos de estudiantes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//estructuras de datos
typedef struct estudiante{
    int cedula;
    char nombre[32];
    int semestre;
} estudiante_t;

typedef struct bd{
    int tamaño;
    char nombrebd[32];
    estudiante_t *registroEstudiante;
    int conteoEst;
} bd_t;

//prototipado de funciones
void mdb(char[32], int);
void loaddb(char[32]);

estudiante_t est;
estudiante_t *pest = &est;
bd_t bd;
bd_t *pbd = &bd;
int indexbd;
int cont=0;
int existebd;

int main(void){
    indexbd =0;
    mdb("bd1",20);
    loaddb("estudiantes.txt");
    mdb("bd2",30);
    loaddb("estudiantes2.txt");
    mdb("bd3",20);
    loaddb("estudiantes3.txt");
    return 0;
}

//funciones
 void mdb(char nombrebd [32], int sizebd){
    existebd =1;
    (pbd+indexbd)->tamaño = sizebd;
    indexbd++;
    cont++;
}

void loaddb(char archivo[32]){
    FILE *archivof; //declara archivo
    char datos[100];
    int linea=0;
    int control;

    printf("%s %d\n","Base de datos activa:",cont-1);
    if(existebd==1){
        //abrir archivo para lectura
        archivof = fopen(archivo,"r");
        //valida que no sea nulo
        if(archivof== NULL){
        printf("No se pudo abrir archivo \n%s", archivo);
        exit(EXIT_FAILURE);
        }
        //reservar
        (pbd+(indexbd-1))->registroEstudiante = (estudiante_t *)malloc(sizeof(estudiante_t)*(pbd+indexbd-1)->tamaño);
        linea = 0;
        //recorrer
        while(fgets(datos,sizeof(datos),archivof)!=NULL){ //lee cada linea
                control++;
                if(control ==1){
                    (pbd+(indexbd-1))->registroEstudiante[linea].cedula= atoi(datos);
                    printf("%d\n",(pbd+(indexbd-1))->registroEstudiante[linea].cedula);
                }
                if(control == 2){
                    strcpy((pbd+(indexbd-1))->registroEstudiante[linea].nombre,datos);
                    printf("%s\n",(pbd+(indexbd-1))->registroEstudiante[linea].nombre);
                }
                if(control == 3){
                    (pbd+(indexbd-1))->registroEstudiante[linea].semestre = atoi(datos);
                    printf("%d\n",(pbd+(indexbd-1))->registroEstudiante[linea].semestre);
                    control=0;
                    linea++;
                }
                (pbd+(indexbd-1))->conteoEst = linea;
        }
        fclose(archivof);  //cerrar archivo
        printf("%s\n","La base de datos fue cargada correctamente");
        }

        else{
            printf("%s\n","La base de datos no se ha creado");
        }
    existebd=0;
}