#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

char respuesta[3];
int sel_sub_menu;

// Definir los datos del empleado
struct Empleado {
    char codigo[50];
    char nombre[50];
    char apellido[50];
    char genero[50];
    char domicilio[100];
    char posicion[50];
    double salario;
};

// Pedir datos del empleado y agregar empleado a un arreglo
struct Empleado *registrar_empleado(struct Empleado *listaEmpleados, int *tamano, int *capacidad) {
    printf("Ingrese los datos del empleado\n");
    do {
        struct Empleado *temp = realloc(listaEmpleados, (*capacidad + 1) * sizeof(struct Empleado));

        if (temp == NULL) {
            printf("Error al asignar memoria. Saliendo del programa...\n");
            free(listaEmpleados);
            exit(1);
        }

        listaEmpleados = temp;
        (*capacidad)++;

        printf("Código: ");
        scanf("%s", listaEmpleados[*tamano].codigo);
        printf("Nombre: ");
        scanf("%s", listaEmpleados[*tamano].nombre);
        printf("Apellido: ");
        scanf("%s", listaEmpleados[*tamano].apellido);
        printf("Género: ");
        scanf("%s", listaEmpleados[*tamano].genero);
        printf("Domicilio: ");
        scanf("%s", listaEmpleados[*tamano].domicilio);
        printf("Posición: ");
        scanf("%s", listaEmpleados[*tamano].posicion);
        printf("Salario: ");
        scanf("%lf", &listaEmpleados[*tamano].salario);

        (*tamano)++;

        printf("¿Desea registrar otro empleado? (si/no): ");
        scanf("%2s", respuesta);
    } while (strcmp(respuesta, "si") == 0);

    return listaEmpleados;
}

// Mostrar los datos de todos los empleados registrados en la lista
void imprimir_lista_empleados(struct Empleado *listaEmpleados, int tamano) {
    printf("---------------------\n");
    printf("Registro de empleados\n");
    for (int i = 0; i < tamano; i++) {
        printf("---------------------\n");
        printf("Código: %s\n", listaEmpleados[i].codigo);
        printf("Nombre: %s\n", listaEmpleados[i].nombre);
        printf("Apellido: %s\n", listaEmpleados[i].apellido);
        printf("Género: %s\n", listaEmpleados[i].genero);
        printf("Domicilio: %s\n", listaEmpleados[i].domicilio);
        printf("Posición: %s\n", listaEmpleados[i].posicion);
        printf("Salario: %.2lf\n", listaEmpleados[i].salario);
    }
    printf("---------------------\n");
}

void sel_invalida() {
    printf("La opción ingresada es inválida.\n");
}

bool salir_sub_menu() {
    printf("¿Desea volver al menú principal? (si/no): ");
    scanf("%2s", respuesta);
    return (strcmp(respuesta, "si") == 0);
}

int main(void) {
    int sel_menu_principal;
    int capacidad = 0;
    int tamano = 0;
    bool repetir_menu_principal = true;
    bool repetir_sub_menu = true;
    struct Empleado *listaEmpleados = NULL;

    do {
        printf("Menú principal\n");
        printf("1. Empleados\n");
        printf("2. Salir\n");
        printf("Ingrese una de las opciones anteriores: ");
        scanf("%d", &sel_menu_principal);

        switch (sel_menu_principal) {
            case 1:
                do {
                    repetir_sub_menu = true;
                    printf("Menú de empleados\n");
                    printf("1. Registrar empleados\n");
                    printf("2. Mostrar registro de empleados\n");
                    printf("3. Salir\n");
                    printf("Ingrese una de las opciones anteriores: ");
                    scanf("%d", &sel_sub_menu);

                    switch (sel_sub_menu) {
                        case 1:
                            listaEmpleados = registrar_empleado(listaEmpleados, &tamano, &capacidad);
                            break;
                        case 2:
                            imprimir_lista_empleados(listaEmpleados, tamano);
                        case 3:
                            if (salir_sub_menu()) {
                                repetir_sub_menu = false;
                            }
                            break;
                        default:
                            sel_invalida();
                            break;
                    }
                } while (repetir_sub_menu);
                break;
            case 2:
                printf("¿Desea salir del programa? (si/no): ");
                scanf("%2s", respuesta);
                if (strcmp(respuesta, "si") == 0) {
                    repetir_menu_principal = false;
                }
                break;
            default:
                sel_invalida();
                break;
        }
    } while (repetir_menu_principal);

    free(listaEmpleados);
    return 0;
}





