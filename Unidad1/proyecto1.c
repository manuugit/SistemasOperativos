//base de datos de estudiantes usando estructuras de datos
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
} bd_t;

//prototipado de funciones
bd_t mkdb(char[32], int);
void loaddb(char[32]);
void savedb(char[32]);

estudiante_t est;
estudiante_t *pest = &est;
bd_t bd;
bd_t *pbd = &bd;
bd_t *buffer;
int existebd=0;

int main(void){
    mkdb("based",3);
    loaddb("/home/manuela/SistemasOperativos/Unidad1/estudiantes.txt");
    return 0;
}

//funciones
 bd_t mkdb(char nombrebd [32], int sizebd){
    bd.tamaño = sizebd;
    existebd=1;
    return bd;
}

void loaddb(char archivo[32]){
    FILE *archivof; //declara archivo
    char datos[100];
    int linea=0;
    int control;

    if(existebd ==1){
        //abrir archivo para lectura
        archivof = fopen(archivo,"r");
        //valida que no sea nulo
        if(archivof== NULL){
        printf("No se pudo abrir archivo \n%s", archivo);
        exit(EXIT_FAILURE);
        }
        //reserva de memoria
        pbd ->registroEstudiante = (estudiante_t *)malloc(sizeof(estudiante_t)*bd.tamaño);
        linea = 0;
        //recorrer
        while(fgets(datos,sizeof(datos),archivof)!=NULL){ //lee cada linea
                control++;
                if(control ==1){
                    pbd->registroEstudiante[linea].cedula= atoi(datos);
                    //printf("%d\n",pbd->registroEstudiante[linea].cedula);
                }
                if(control == 2){
                    strcpy(pbd->registroEstudiante[linea].nombre,datos);
                    //printf("%s\n",pbd->registroEstudiante[linea].nombre);
                }
                if(control == 3){
                    pbd->registroEstudiante[linea].semestre = atoi(datos);
                    //printf("%d\n",pbd->registroEstudiante[linea].semestre);
                    control=0;
                    linea++;
                }
        }
        for (int i=0; i<bd.tamaño; i++){
          printf("%d  %s %d\n",pbd->registroEstudiante[i].cedula,pbd->registroEstudiante[i].nombre,pbd->registroEstudiante[i].semestre);
        }
        fclose(archivof);  //cerrar archivo
        printf("%s\n","La base de datos fue cargada correctamente");
        }

        else{
            printf("%s\n","La base de datos no se ha creado");
        }
    
}

void savedb(char archivoSalida[32]){
    //abrir archivo para escritura
    /*FILE *archivoS =fopen(archivoSalida,"w");
    if (archivoSalida == NULL) {
        perror("Error: ");
        return EXIT_FAILURE;
    }
    for (int i=0; i)*/
}