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
void gdb();
void sdb(char[32]);
void svdb();
void radb();
int rsdb();
void mreg(int,char[52],int);
void rr(int);
char exitP();

estudiante_t est;
estudiante_t *pest = &est;
libd_t listabd;
libd_t *plbd= &listabd;
int activa=0;
char archivoact[32];

int main(void){
    int maximobd =20;
    listabd.conteobd=0;
    char comando [32];
    char par1 [20];
    char par2 [20];
    char par3 [20];
    char salir;
    char fileF [32];
    //reserva de memoria para todas las bd
    plbd->pdatabase = (bd_t *)malloc(sizeof(bd_t)*maximobd);

     while(strcmp(comando,"exitP")!=0){
        printf("\n%s","Escriba el comando\n");
        scanf("\n%s",comando);
        if (strcmp(comando,"mdb")==0){
            scanf("%s %s",par1,par2);
            mdb(par1, atoi(par2));
        }
        else if (strcmp(comando,"ldb")==0){
            scanf("%s",par1);
            printf("%s\n",par1);
            ldb(par1);
        }
        else if (strcmp(comando,"lsdbs")==0){
            lsdbs();
        }
        else if (strcmp(comando,"gdb")==0){
            gdb();
        }
        else if (strcmp(comando,"sdb")==0){
            scanf("%s",par1);
            sdb(par1);
            strcpy(fileF, par1);
        }
        else if (strcmp(comando,"svdb")==0){
            svdb();
        }
        else if (strcmp(comando,"radb")==0){
            radb();
        }
        else if (strcmp(comando,"rsdb")==0){
            printf("%s %d\n","Cantidad de registros=",rsdb());
        }
        else if (strcmp(comando,"mreg")==0){
            scanf("%s %s %s",par1,par2,par3);
            mreg(atoi(par1),par2, atoi(par3));
        }
        else if (strcmp(comando,"rr")==0){
            scanf("%s",par1);
            rr(atoi(par1));
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
        svdb(fileF);
        printf("Los datos se guardaron correctamente\n");
    }
    else{
        printf("Los datos no se guardaron\n");
    }

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
                    //printf("%d\n",(listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[linea].cedula);
                }
                if(control == 2){
                    strcpy((listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[linea].nombre,datos);
                    //printf("%s\n",(listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[linea].nombre);
                }
                if(control == 3){
                    (listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[linea].semestre = atoi(datos);
                    //printf("%d\n",(listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[linea].semestre);
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
    printf("%s\n","Bases de datos en memoria:");
    for(int i=0; i<listabd.conteobd; i++){
        printf("%s %s|","Nombre",listabd.pdatabase[i].nombrebd);
        printf("%s %d|","Tamaño max",listabd.pdatabase[i].tamaño);
        printf("%s %d\n","Cantidad de registros",listabd.pdatabase[i].conteoEst);
    }
}

void gdb(){
    printf("%s\n","Base de datos activa:");
    printf("%s %s|","Nombre",listabd.pdatabase[listabd.conteobd-1].nombrebd);
    printf("%s %d|","Tamaño max",listabd.pdatabase[listabd.conteobd-1].tamaño);
    printf("%s %d\n","Cantidad de registros disponibles",(listabd.pdatabase[listabd.conteobd-1].tamaño-listabd.pdatabase[listabd.conteobd-1].conteoEst));
}

void sdb(char nombre[32]){
    activa=1;
    strcpy(archivoact,listabd.pdatabase[listabd.conteobd-1].nombrebd);
    strcat(archivoact,".txt");
}

void svdb(){
    if (activa ==1){
    //abrir archivo para escritura
    FILE *archivoS =fopen(archivoact,"w");
    if (archivoact== NULL) {
        exit(EXIT_FAILURE);
    }
    fprintf(archivoS,"ESTUDIANTES\n");
    fprintf(archivoS,"Cédula|Nombre|Semestre\n");
    for (int i=0; i< ((listabd.pdatabase+(listabd.conteobd-1))->conteoEst); i++){
        fprintf(archivoS,"%d ",(listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[i].cedula);
        fprintf(archivoS,"%s ",(listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[i].nombre);
        fprintf(archivoS,"%d\n",(listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[i].semestre);
    }

    fclose(archivoS);
    printf("%s %s %s %s\n", "La base de datos",(listabd.pdatabase+(listabd.conteobd-1))->nombrebd,"se escribió en el archivo",archivoact);
    }

    else{
        printf("%s\n","Antes de usar este comando debe aplicar sdb nombre");
    }
}

void radb(){
    if(activa ==1){
        for (int i=0; i<(listabd.pdatabase+(listabd.conteobd-1))->conteoEst; i++){
        printf("%d ",(listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[i].cedula);
        printf("%s ",(listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[i].nombre);
        printf("%d\n",(listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[i].semestre);
    }
    }
    else{
        printf("%s\n","Antes de usar este comando debe aplicar sdb nombre");
    }
}

int rsdb(){
    if(activa ==1){
        return (listabd.pdatabase+(listabd.conteobd-1))->conteoEst;
    }
    else{
        printf("%s\n","Antes de usar este comando debe aplicar sdb nombre");
        return(-1);
    }
}

void mreg(int cedula, char nombreEst[52],int semestre){
    if (activa ==1){
        if ((listabd.pdatabase+(listabd.conteobd-1))->conteoEst < (listabd.pdatabase+(listabd.conteobd-1))->tamaño){
            (listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[(listabd.pdatabase+(listabd.conteobd-1))->conteoEst].cedula= cedula;
            strcpy((listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[(listabd.pdatabase+(listabd.conteobd-1))->conteoEst].nombre,nombreEst);
            (listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[(listabd.pdatabase+(listabd.conteobd-1))->conteoEst].semestre= semestre;
            (listabd.pdatabase+(listabd.conteobd-1))->conteoEst = ((listabd.pdatabase+(listabd.conteobd-1))->conteoEst)+1;
    }
        else{
            printf("Ya se alcanzo la capacidad maxima de la base de datos");
        }
    }
    else{
        printf("%s\n","Antes de usar este comando debe aplicar sdb nombre");
    }
    
}

void rr(int cedula){
    int encontro = 0;
    for (int i=0; i< ((listabd.pdatabase+(listabd.conteobd-1))->tamaño); i++){
        if ((listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[i].cedula == cedula){
             printf("%d %s %d\n ",(listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[i].cedula,(listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[i].nombre,(listabd.pdatabase+(listabd.conteobd-1))->registroEstudiante[i].semestre);
            encontro = 1;
            i = (listabd.pdatabase+(listabd.conteobd-1))->tamaño;
        }
    }
    if(encontro !=1){
        printf("%s %s\n","Cedula no encontrada en",(listabd.pdatabase+(listabd.conteobd-1))->nombrebd);
    }
}

char exitP(){
    char r,key;
    scanf("%c",&key);
    printf("%s\n", "¿Desea guardar los cambios de la base de datos en el archivo?\ns para si, n para no");
    scanf("%c",&r);
    return(r);
}
