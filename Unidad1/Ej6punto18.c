//programa que lee un archivo de notas (formato propuesto: materia:\n nota:\n creditos:\n con n materias) y calcula el promedio ponderado del estudiante escribiendo en otro archivo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    char linea[50];
    char nombreA1 [50] = "archivo1.txt";
    char nombreA2 [50] = "salida.txt";
    int creditos[10];
    float notas[10];
    int contLinea, contMateria, control, totalCreditos;
    float promedio;
    char materiatmp [50];
    char materiasG [100]="";
    char materiasP [100]="";
    //abrir archivo para lectura
    FILE *archivoEntrada = fopen(nombreA1, "r");
    if (archivoEntrada == NULL) {
        perror("Error: ");
        return EXIT_FAILURE;
    }

    //abrir archivo para escritura
    FILE *archivoSalida= fopen(nombreA2, "w");
    if (archivoSalida == NULL) {
        perror("Error: ");
        return EXIT_FAILURE;
    }

    fprintf(archivoSalida,"Materia|Nota|Creditos\n");
    contMateria=0;
    while (fgets(linea, sizeof(linea), archivoEntrada) != NULL) {
        contLinea++;
        if(contLinea % 2 == 0){
            control++;
            fprintf(archivoSalida,linea,"%s ");
            if(control ==1){
                strcpy(materiatmp,linea);
            }
            if(control == 2){
                notas[contMateria] = atof(linea);
                if(notas[contMateria]>=3){
                    strcat(materiasG,materiatmp);
                }
                else{
                    strcat(materiasP,materiatmp);
                }
            }
            if(control == 3){
                creditos[contMateria] = atoi(linea);
                totalCreditos = totalCreditos + creditos[contMateria];
                control=0;
                contMateria++;
            }
        }
    }
    //calculos para el promedio
    promedio=0;
    for (int i=0; i<contMateria;i++){
        promedio = promedio + (notas[i]*creditos[i]);
    }
    promedio = (promedio / totalCreditos);
    printf("%f Datos se escribieron en el archivo\n",promedio);

    //pasar info al archivo de salida
    fprintf(archivoSalida,"Total de materias:");
    fprintf(archivoSalida,"%d\n",(contMateria));
    fprintf(archivoSalida,"Materias ganadas:\n");
    fputs(materiasG,archivoSalida);
    fprintf(archivoSalida,"Materias perdidas:\n");
    fputs(materiasP,archivoSalida);
    fprintf(archivoSalida,"Promedio ponderado:");
    fprintf(archivoSalida,"%.2f\n",promedio);
    
    //cerrar archivos
    fclose(archivoEntrada);
    fclose(archivoSalida);

    return EXIT_SUCCESS;
}