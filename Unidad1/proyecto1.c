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
    int conteoEst;
} bd_t;

//prototipado de funciones
bd_t mkdb(char[32], int);
void loaddb(char[32]);
void savedb(char[32]);
void readall(void);
int readsize(void);
void mkreg(int, char[32], int);
void readreg(int);
char exitP(void);

estudiante_t est;
estudiante_t *pest = &est;
bd_t bd;
bd_t *pbd = &bd;
int existebd=0;

int main(void){
    char comando [32];
    char par1 [20];
    char par2 [20];
    char par3 [20];
    char salir;
    char fileF [32];

     while(strcmp(comando,"exitP")!=0){
        printf("\n%s","Escriba el comando\n");
        scanf("\n%s",comando);
        if (strcmp(comando,"mkdb")==0){
            scanf("%s %s",par1,par2);
            mkdb(par1, atoi(par2));
        }
        else if (strcmp(comando,"loaddb")==0){
            scanf("%s",par1);
            printf("%s\n",par1);
            loaddb(par1);
            strcpy(fileF, par1);
        }
        else if (strcmp(comando,"savedb")==0){
            scanf("%s",par1);
            savedb(par1);
        }
        else if (strcmp(comando,"readall")==0){
            readall();
        }
        else if (strcmp(comando,"readsize")==0){
            printf("%s %d","Cantidad de registros=",readsize());
        }
        else if (strcmp(comando,"mkreg")==0){
            scanf("%s %s %s",par1,par2,par3);
            mkreg(atoi(par1),par2, atoi(par3));
        }
        else if (strcmp(comando,"readreg")==0){
            scanf("%s",par1);
            readreg(atoi(par1));
        }
        else if (strcmp(comando,"exitP")==0){
            printf("\n");
        }
        else{
            printf("Opcion invalida\n");
        }

        printf("Si desea salir utilice el comando exitP\n");
    }
        
    salir = exitP();
     if (salir== 's'){
        savedb(fileF);
        printf("Los datos se guardaron correctamente\n");
    }
    else{
        printf("Los datos no se guardaron\n");
    }
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
                pbd->conteoEst = linea;
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
    FILE *archivoS =fopen(archivoSalida,"w");
    if (archivoSalida == NULL) {
        exit(EXIT_FAILURE);
    }
    fprintf(archivoS,"ESTUDIANTES\n");
    fprintf(archivoS,"Cédula|Nombre|Semestre\n");
    for (int i=0; i< (pbd->conteoEst); i++){
        fprintf(archivoS,"%d ",pbd->registroEstudiante[i].cedula);
        fprintf(archivoS,"%s ",pbd->registroEstudiante[i].nombre);
        fprintf(archivoS,"%d\n",pbd->registroEstudiante[i].semestre);
    }

    fclose(archivoS);

    printf("%s %s %s %s\n", "La base de datos",pbd->nombrebd,"se escribió en el archivo",archivoSalida);
}

void readall(void){
    for (int i=0; i< (bd.conteoEst); i++){
        printf("%d ",pbd->registroEstudiante[i].cedula);
        printf("%s ",pbd->registroEstudiante[i].nombre);
        printf("%d\n",pbd->registroEstudiante[i].semestre);
    }
}

int readsize(void){
    return pbd->conteoEst;
}

void mkreg(int cedula, char nombre[32], int semestre){
    if (bd.conteoEst < bd.tamaño){
        pbd->registroEstudiante[bd.conteoEst].cedula= cedula;
        strcpy(pbd->registroEstudiante[bd.conteoEst].nombre,nombre);
        pbd->registroEstudiante[bd.conteoEst].semestre= semestre;
        bd.conteoEst = bd.conteoEst+1;
    }
    else{
        printf("Ya se alcanzo la capacidad maxima de la base de datos");
    }
}

void readreg(int cedula){
    int encontro = 0;
    for (int i=0; i< (pbd->tamaño); i++){
        if (pbd->registroEstudiante[i].cedula == cedula){
             printf("%d %s %d\n ",pbd->registroEstudiante[i].cedula,pbd->registroEstudiante[i].nombre,pbd->registroEstudiante[i].semestre);
            encontro = 1;
            i = bd.tamaño;
        }
    }
    if(encontro !=1){
        printf("Cedula no encontrada\n");
    }
}

char exitP(void){
    char r,key;
    scanf("%c",&key);
    printf("%s\n", "¿Desea guardar los cambios de la base de datos en el archivo?\ns para si, n para no");
    scanf("%c",&r);
    return(r);
}