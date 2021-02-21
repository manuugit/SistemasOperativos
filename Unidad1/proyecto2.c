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
    int existebd;
} bd_t;

typedef struct listabd{
    bd_t *pdatabase;
    int conteobd;
} libd_t;

//prototipado de funciones
void mdb(char[32], int);
void ldb(char[32]);
void lsdbs();

estudiante_t est;
estudiante_t *pest = &est;
libd_t listabd;
libd_t *plbd= &listabd;

int main(void){
    int maximobd =20;
    listabd.conteobd=0;
    //reserva de memoria para todas las bd
    plbd->pdatabase = (bd_t *)malloc(sizeof(bd_t)*maximobd);
    mdb("bd1",20);
    ldb("estudiantes.txt");
    mdb("bd2",20);
    ldb("estudiantes2.txt");
    mdb("bd3",20);
    ldb("estudiantes3.txt");
    mdb("bd4",30);
    ldb("estudiantes2.txt");
    lsdbs();
    free(plbd->pdatabase);
    return 0;
}

//funciones
 void mdb(char nombrebd [32], int sizebd){
    strcpy((listabd.pdatabase+listabd.conteobd)->nombrebd,nombrebd);
    (listabd.pdatabase+listabd.conteobd)->tamaño = sizebd;
    (listabd.pdatabase+listabd.conteobd)->existebd = 1;
    listabd.conteobd++;
    (listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante = (estudiante_t *)malloc(sizeof(estudiante_t)*(listabd.pdatabase+listabd.conteobd-1)->tamaño);
}

void ldb(char archivo[32]){
    FILE *archivof; //declara archivo
    char datos[100];
    int linea=0;
    int control=0;

    printf("%s %d\n","Base de datos activa:",listabd.conteobd-1);
    if((listabd.pdatabase+(listabd.conteobd-1))->existebd == 1){
        //abrir archivo para lectura
        archivof = fopen(archivo,"r");
        //valida que no sea nulo
        if(archivof== NULL){
        printf("No se pudo abrir archivo \n%s", archivo);
        exit(EXIT_FAILURE);
        }

        linea = 0;
        //recorrer
        while(fgets(datos,sizeof(datos),archivof)!=NULL){ //lee cada linea
                control++;
                if(control ==1){
                    (listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[linea].cedula= atoi(datos);
                    printf("%d\n",(listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[linea].cedula);
                }
                if(control == 2){
                    strcpy((listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[linea].nombre,datos);
                    printf("%s\n",(listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[linea].nombre);
                }
                if(control == 3){
                    (listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[linea].semestre = atoi(datos);
                    printf("%d\n",(listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[linea].semestre);
                    control=0;
                    linea++;
                }
                (listabd.pdatabase+(listabd.conteobd-1))->conteoEst = linea;
        }
        fclose(archivof);  //cerrar archivo
        printf("%s\n","La base de datos fue cargada correctamente");
     }

    else{
        printf("%s\n","La base de datos no se ha creado");
    }
}

void lsdbs(){
    for(int i=0; i<listabd.conteobd; i++){
        printf("%s ",listabd.pdatabase[i].nombrebd);
        printf("%d ",listabd.pdatabase[i].tamaño);
        printf("%d\n",listabd.pdatabase[i].conteoEst);
    }
   
}