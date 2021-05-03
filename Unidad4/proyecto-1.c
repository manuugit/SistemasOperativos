//leer el contenido de un directorio y de sus subdirectorios
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

char tipoRetornado [32];
int control;

// Prototipado de funciones
void identificarTipo(char ruta [512]);
void listarDirectorio(char ruta [512]);

void unix_error(char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

int main(int argc, char **argv)
{
    char tipo [32];
    char ruta [512];
    strcpy(ruta,argv[1]);

    if (argc != 2) {
        printf("usage: %s <pathname>\n", argv[0]);
        exit(1);
    }

    identificarTipo(ruta);
    strcpy(tipo,tipoRetornado);
        
    if (strcmp(tipo, "directory")!=0){
        printf("No es posible recorrer el directorio, porque la ruta no corresponde a un directorio");
    }
    else{
        listarDirectorio(ruta);
    }
    
    return(0);


}

void identificarTipo(char ruta [512]){
    struct stat stat_str;
    stat(ruta, &stat_str);
    
    if (S_ISREG(stat_str.st_mode))     /* Determine file type */
	  strcpy(tipoRetornado,"regular");
    else if (S_ISDIR(stat_str.st_mode))
	  strcpy(tipoRetornado,"directory");
    else 
	  strcpy(tipoRetornado,"other");
}

void listarDirectorio(char ruta [512]){
    DIR *streamp; 
    struct dirent *dep; 
    control++;
    char nuevaRuta [512];
    char tipo [32];

    streamp = opendir(ruta);
    errno = 0;
    

    while ((dep = readdir(streamp)) != NULL) {
        if(strcmp(dep->d_name, "..")!=0 && strcmp(dep->d_name, ".")!=0){
             for(int i=0; i<=control;i++){
                printf("-");
            }
            strcpy(nuevaRuta, ruta);
            //printf("%s\n", nuevaRuta);
            strcat(nuevaRuta, dep->d_name);
            //printf("%s\n", nuevaRuta);
           
            identificarTipo(nuevaRuta);
            strcpy(tipo,tipoRetornado);
           
            //printf("%s",control);
            if (strcmp(tipo, "directory")==0){
                printf("Directorio: %s\n", dep->d_name);
                //printf("rutaA %s\n",nuevaRuta);
                strcat(nuevaRuta, "/");
                listarDirectorio(nuevaRuta);
                //printf("ruta %s\n",nuevaRuta);
            }
            else {
                printf("Archivo %s\n", dep->d_name);
            }       
        } 
    }

    if (errno != 0)
        unix_error("readdir error");

    control--;
    closedir(streamp);
}