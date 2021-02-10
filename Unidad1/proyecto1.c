//base de datos de estudiantes usando estructuras de datos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct estudiante{
    int cedula;
    char nombre[32];
    int semestre;
} estudiante_t;

typedef struct bd{
    int tamaño;
    char nombrebd[32];
    estudiante_t *registroEstudiante;
} bd_t;

bd_t mkdb(char[32], int);
void loaddb(char[32], char[32]);
estudiante_t est;
estudiante_t *pest = &est;
bd_t bd;
bd_t *pbd = &bd;
bd_t *buffer;

int main(void){
    mkdb("based",3);
    loaddb("based","/home/manuela/SistemasOperativos/Unidad1/estudiantes.txt");
    return 0;
}

//funciones
 bd_t mkdb(char nombrebd [32], int sizebd){
    bd.tamaño = sizebd;
    return bd;
}

void loaddb(char nombrebd [32], char archivo[32]){
    FILE *archivof; //declara archivo
    char datos[100];
    int linea=0;
    int control;
    //abrir archivo para lectura
    archivof = fopen(archivo,"r");
    //valida que no sea nulo
    if(archivof== NULL){
        printf("No se pudo abrir archivo \n%s", archivo);
        exit(EXIT_FAILURE);
    }
    //reserva de memoria
    buffer = (bd_t *)malloc(sizeof(est)*bd.tamaño);
    linea = 0;
    //recorrer
    while(fgets(datos,sizeof(datos),archivof)!=NULL){ //lee cada linea
            control++;
            if(control ==1){
                (pest+linea)->cedula= atoi(datos);
                //printf("%d\n",(pest+linea)->cedula);
            }
            if(control == 2){
                strcpy((pest+linea)->nombre,datos);
                //printf("%s\n",(pest+linea)->nombre);
            }
            if(control == 3){
                (pest+linea)->semestre = atoi(datos);
                //printf("%d\n",(pest+linea)->semestre);
                control=0;
                linea++;
            }
        pbd ->registroEstudiante = (pest+linea);
    }
    for (int i=0; i<bd.tamaño; i++){
       // printf("%d %d %s %d\n",i,(pest+i)->cedula,(pest+i)->nombre,(pest+i)->semestre);
        printf("%d,%s %d",(pbd->registroEstudiante+i)->cedula,(pbd->registroEstudiante+i)->nombre,(pbd->registroEstudiante+i)->semestre);
    }
    buffer = pbd;
    fclose(archivof);  //cerrar archivo
    printf("%s\n","Se procesó y escribió archivo");
}
