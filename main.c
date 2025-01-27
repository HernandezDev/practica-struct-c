#include<stdio.h>
#include<stdbool.h>
#include<string.h>

struct alumno
{
    int dni;
    char apellido[20];
    char nombre[20];
    char segundo_nombre[20];
    float primer_parcial, segundo_parcial, primer_recuperatorio,segundo_recuperatorio, promedio;
    
};

int CargarNumero();
int MostarMenu();
void CargarAlumnos(struct alumno alumnos[], int *NumAlumno);
void OdenarPromdio(struct alumno alumnos[], int NumAlumno);
void OrdenarApellido(struct alumno alumnos[], int NumAlumno);
void MostrarAlumnos(struct alumno alumnos[], int NumAlumno, bool recursantes);
void BuscarDNI(struct alumno alumnos[], int NumAlumno);


int main()
{
    struct alumno alumnos[100];
    int NumAlumno=0, opcion;
    bool salir = false;
    while (!salir)
    {
        opcion = MostarMenu();
        switch (opcion)
        {
            case 1:
                CargarAlumnos(alumnos, &NumAlumno);
                break;
            case 2:
                OdenarPromdio(alumnos, NumAlumno);
                MostrarAlumnos(alumnos, NumAlumno, false);
                break;
            case 3:
                OrdenarApellido(alumnos, NumAlumno);
                MostrarAlumnos(alumnos, NumAlumno, false);
                break;
            case 4:
                MostrarAlumnos(alumnos, NumAlumno, true);
                break;
            case 5:
                BuscarDNI(alumnos, NumAlumno);
                break;
            case 6:
                salir = true;
                break;
        }
    }
    return 0;
}

int CargarNumero()
{
    int numero;
    if(scanf("%d", &numero)!=1)
    {
        printf("Entrada no válida. Por favor, \n ingrese un número:");
        // Limpiar el buffer de entrada
        while (getchar() != '\n');
        // Volver a pedir el número
        numero = CargarNumero();
    }
    return numero;
}

int MostarMenu()
{
    int opcion;
    printf("1. Cargar Alumnos\n");
    printf("2. Mostrar Alumnos por promedio\n");
    printf("3. Mostrar Alumnos por orden alfabético\n");
    printf("4. Mostrar Recursantes\n");
    printf("5. Buscar por DNI\n");
    printf("6. Salir\n");
    printf("Ingrese una opcion: ");
    if(scanf("%d", &opcion)!=1)
    {
        printf("Entrada no válida. Por favor, ingrese un número\n");
        // Limpiar el buffer de entrada
        while (getchar() != '\n');
        // Volver a pedir el número
        opcion = MostarMenu();
    }
    return opcion;
}

void CargarAlumnos(struct alumno alumnos[], int *NumAlumno)
{
    bool salir = false;
    while (!salir)
    {
        printf("Ingrese el DNI del alumno: ");
        alumnos[*NumAlumno].dni = CargarNumero();
        if (alumnos[*NumAlumno].dni == 0)
        {
            break;
        }
        alumnos[*NumAlumno].promedio = 0;
        printf("Ingrese el apellido del alumno: ");
        scanf("%s", alumnos[*NumAlumno].apellido);
        printf("Ingrese el nombre del alumno: ");
        scanf("%s", alumnos[*NumAlumno].nombre);
        printf("Ingrese el segundo nombre del alumno: ");
        scanf("%s", alumnos[*NumAlumno].segundo_nombre);
        printf("Ingrese la nota del primer parcial: ");
        alumnos[*NumAlumno].primer_parcial = CargarNumero();
        if (alumnos[*NumAlumno].primer_parcial < 4)
        {
            printf("Ingrese la nota del primer recuperatorio: ");
            alumnos[*NumAlumno].primer_recuperatorio = CargarNumero();
            alumnos[*NumAlumno].promedio += alumnos[*NumAlumno].primer_recuperatorio;
        }
        else
        {
            alumnos[*NumAlumno].promedio += alumnos[*NumAlumno].primer_parcial;
        }
        printf("Ingrese la nota del segundo parcial: ");
        alumnos[*NumAlumno].segundo_parcial = CargarNumero();
        if (alumnos[*NumAlumno].segundo_parcial < 4)
        {
            printf("Ingrese la nota del segundo recuperatorio: ");
            alumnos[*NumAlumno].segundo_recuperatorio = CargarNumero();
            alumnos[*NumAlumno].promedio += alumnos[*NumAlumno].segundo_recuperatorio;
            
        }
        else
        {
            alumnos[*NumAlumno].promedio += alumnos[*NumAlumno].segundo_parcial;
        }
        alumnos[*NumAlumno].promedio /= 2;
        (*NumAlumno)++;
    }    
}

void OdenarPromdio(struct alumno alumnos[], int NumAlumno)
{
    bool ordenado = false;
    int i;
    
    while (!ordenado)
    {
        ordenado = true;
        for (i = 0; i < NumAlumno - 1; i++)
        {
            if (alumnos[i].promedio < alumnos[i + 1].promedio)
            {
                struct alumno aux = alumnos[i];
                alumnos[i] = alumnos[i + 1];
                alumnos[i + 1] = aux;
                ordenado = false;
            }
        }
        NumAlumno--;
    }
}

void OrdenarApellido(struct alumno alumnos[], int NumAlumno)
{
    bool ordenado = false;
    while (!ordenado)
    {
        ordenado = true; // Asumimos que está ordenado
        for (int i = 0; i < NumAlumno - 1; i++)
        {
            if (strcmp(alumnos[i].apellido, alumnos[i + 1].apellido) > 0)
            {
                struct alumno aux = alumnos[i];
                alumnos[i] = alumnos[i + 1];
                alumnos[i + 1] = aux;
                ordenado = false;
            }
            else if (strcmp(alumnos[i].apellido, alumnos[i + 1].apellido) == 0)
            {
                if (strcmp(alumnos[i].nombre, alumnos[i + 1].nombre) > 0)
                {
                    struct alumno aux = alumnos[i];
                    alumnos[i] = alumnos[i + 1];
                    alumnos[i + 1] = aux;
                    ordenado = false;
                }
                else if (strcmp(alumnos[i].nombre, alumnos[i + 1].nombre) == 0)
                {
                    if (strcmp(alumnos[i].segundo_nombre, alumnos[i + 1].segundo_nombre) > 0)
                    {
                        struct alumno aux = alumnos[i];
                        alumnos[i] = alumnos[i + 1];
                        alumnos[i + 1] = aux;
                        ordenado = false;
                    }
                }
            }
        }
        NumAlumno--;
    }
}

void MostrarAlumnos(struct alumno alumnos[], int NumAlumno,bool recursantes)
{
    int i;
    printf("1erPar\t1erRec\t2doPar\t2doRec\tProm\tApellido/Nombre/2doNomre\n");
    for (i = 0; i < NumAlumno; i++)
    {
        if (recursantes && alumnos[i].promedio >= 4)
        {
            continue;
        }
        printf("%.2f\t", alumnos[i].primer_parcial);
        if(alumnos[i].primer_parcial < 4)
        {
            printf("%.2f\t", alumnos[i].primer_recuperatorio);
        }
        else
        {
            printf("\t");
        }
        printf("%.2f\t", alumnos[i].segundo_parcial);
        if(alumnos[i].segundo_parcial < 4)
        {
            printf("%.2f\t", alumnos[i].segundo_recuperatorio);
        }
        else
        {
            printf("\t");
        }
        printf("%.2f\t%s %s %s\n", alumnos[i].promedio, alumnos[i].apellido, alumnos[i].nombre, alumnos[i].segundo_nombre);
    }
}

void BuscarDNI(struct alumno alumnos[], int NumAlumno)
{
    int dni, i;
    printf("Ingrese el DNI a buscar: ");
    dni = CargarNumero();
    for (i = 0; i < NumAlumno; i++)
    {
        if (alumnos[i].dni == dni)
        {
            printf("DNI: %d\n", alumnos[i].dni);
            printf("Apellido: %s\n", alumnos[i].apellido);
            printf("Nombre: %s\n", alumnos[i].nombre);
            printf("Segundo nombre: %s\n", alumnos[i].segundo_nombre);
            printf("1er parcial: %.2f\n", alumnos[i].primer_parcial);
            if (alumnos[i].primer_parcial < 4)
            {
                printf("1er recuperatorio: %.2f\n", alumnos[i].primer_recuperatorio);
            }
            printf("2do parcial: %.2f\n", alumnos[i].segundo_parcial);
            if (alumnos[i].segundo_parcial < 4)
            {
                printf("2do recuperatorio: %.2f\n", alumnos[i].segundo_recuperatorio);
            }
            printf("Promedio: %.2f\n", alumnos[i].promedio);
            return;
        }
    }
    printf("No se encontró el DNI\n");
}
