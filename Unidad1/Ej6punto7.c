//
#include <stdio.h>

typedef struct estudiante
{
    char Nombre[40];
    int numEstudiante;
    int agnoMatricula;
    float nota;
} est; //declara tipo de variable

void actualizarMiembros (est *estudi); //prototipar funcion

int main(void)
{
    struct estudiante estud1={"Jose",4,2009,4.5};
    struct estudiante *ptrEstruct;
    ptrEstruct = &estud1;
    char tecla;

    //impresion de todos los miembros de estructura estudiante
    printf("|%-20s|%-5s|%-4s|%4s|\n", "Nombre", "# estudiante","Año","Nota");
    printf("con apuntador\n");
    printf("%-20s|%-5d|%-4d|%4.2f \n",ptrEstruct->Nombre,ptrEstruct->numEstudiante,ptrEstruct->agnoMatricula, ptrEstruct->nota);
    printf("sin apuntador\n");
    printf("%-20s|%-5d|%-4d|%4.2f\n", estud1.Nombre,estud1.numEstudiante,estud1.agnoMatricula,estud1.nota);
    printf("Si desea actualizar los datos del estudiante presione 'r', si no presione 's'\n");
    scanf("%c",&tecla);
    if(tecla == 'r'){
        actualizarMiembros(ptrEstruct);
        printf("Nuevos datos:\n%-20s|%-5d|%-4d|%4.2f\n", estud1.Nombre,estud1.numEstudiante,estud1.agnoMatricula,estud1.nota);
    }
    else
    {
        printf("Los datos no se han actualizado\n");
    }
    
    return(0);

}

//funcion para actualizar los miembros, se utiliza el puntero a estudiante
void actualizarMiembros(est *estudi){
   printf("Escriba nombre\n");
   scanf("%s",estudi->Nombre);
   printf("Escriba num de estudiante\n");
   scanf("%d",&estudi->numEstudiante);
   printf("Escriba año matricula\n");
   scanf("%d",&estudi->agnoMatricula);
   printf("Escriba nota\n");
   scanf("%f",&estudi->nota);
}