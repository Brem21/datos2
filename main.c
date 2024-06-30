#include <stdio.h>
#include <string.h>
#include "funciones.h"

// Declaraciones de funciones
void buscarPorTamano(int *numHabitacion, char habitaciones[][3][40], double precios[]);
void buscarHotel(int *numHabitacion, char habitaciones[][3][40], double precios[]);
void realizarReserva(int numHabitacion, char habitaciones[][3][40], char clientes[][2][40], int reservas[][4], double precios[]);
void buscarReservaPorCedula(int *numReserva, char clientes[][2][40], int reservas[][4]);
void imprimirReserva(int numReserva, int reservas[][4], char habitaciones[][3][40], double precios[]);
void pagarReserva(int numReserva, int reservas[][4], char habitaciones[][3][40], double precios[]);

// Macro para registrar funciones en un archivo
#define REGISTRAR_FUNCION(nombre) fprintf(archivo, #nombre "\n");

int main (int argc, char *argv[]) {
    char clientes[5][2][40]={{"Juan","1789654123"},
                             {"",""},
                             {"",""},
                             {"",""},
                             {"",""}};

    char habitaciones[9][3][40]={{"1","simple","Dan Carlton"},
                                  {"2","doble","Dan Carlton"},
                                  {"3","triple","Dan Carlton"},
                                  {"4","simple","Swissotel"},
                                  {"5","doble","Swissotel"},
                                  {"6","triple","Swissotel"},
                                  {"7","simple","Sheraton"},
                                  {"8","doble","Sheraton"},
                                  {"9","triple","Sheraton"}};

    double precios[9]={90,120,160,65,100,140,85,110,150};

    int reservas[10][4]={{-1,-1,-1,0},
                         {-1,-1,-1,0},
                         {-1,-1,-1,0},
                         {-1,-1,-1,0},
                         {-1,-1,-1,0},
                         {-1,-1,-1,0},
                         {-1,-1,-1,0},
                         {-1,-1,-1,0},
                         {-1,-1,-1,0},
                         {-1,-1,-1,0}};

    int opcion,numHabitacion,numReserva;
    FILE *archivo;
    archivo = fopen("funciones.txt", "w"); // Abrir el archivo para guardar las funciones

    if (archivo == NULL) {
        printf("Error al abrir el archivo!\n");
        return 1;
    }

    // Registrar todas las funciones
    REGISTRAR_FUNCION(main)
    REGISTRAR_FUNCION(buscarPorTamano)
    REGISTRAR_FUNCION(buscarHotel)
    REGISTRAR_FUNCION(realizarReserva)
    REGISTRAR_FUNCION(buscarReservaPorCedula)
    REGISTRAR_FUNCION(imprimirReserva)
    REGISTRAR_FUNCION(pagarReserva)

    do
    {   
        printf("Escoja una opcion:\n 1.Buscar Habitacion\n 2.Realizar reserva\n 3.Ver reservas\n 4.Pagar Reserva\n>>");
        scanf("%d",&opcion);
        switch (opcion)
        {
        case 1:
            printf("1.Por tamaño\n2.Por Hotel\n>>");
            scanf("%d",&opcion);
            switch (opcion)
            {
            case 1:
                buscarPorTamano(&numHabitacion,habitaciones,precios);
                break;
            case 2:
                buscarHotel(&numHabitacion,habitaciones,precios);      
            default:
                break;
            }
            break;
        case 2:
            realizarReserva(numHabitacion,habitaciones,clientes,reservas,precios);
            fprintf(archivo, "Reserva realizada:\nCliente: %s\nCédula: %s\nHabitación: %s (%s) en %s\nPrecio: %.2f\n\n",
                    clientes[numHabitacion - 1][0], clientes[numHabitacion - 1][1], 
                    habitaciones[numHabitacion - 1][0], habitaciones[numHabitacion - 1][1], 
                    habitaciones[numHabitacion - 1][2], precios[numHabitacion - 1]);
            break;
        case 3:
            buscarReservaPorCedula(&numReserva,clientes,reservas);
            imprimirReserva(numReserva,reservas,habitaciones,precios);
            fprintf(archivo, "Detalles de la reserva:\nNúmero de Reserva: %d\nCliente: %s\nCédula: %s\nHabitación: %s\nTipo de Habitación: %s\nHotel: %s\nPrecio: %.2f\nEstado: %s\n\n",
                    numReserva, clientes[reservas[numReserva][1]][0], clientes[reservas[numReserva][1]][1],
                    habitaciones[reservas[numReserva][2]][0], habitaciones[reservas[numReserva][2]][1], 
                    habitaciones[reservas[numReserva][2]][2], precios[reservas[numReserva][2]],
                    reservas[numReserva][3] == 1 ? "Pagada" : "Cancelada");
            break;
        case 4:
            buscarReservaPorCedula(&numReserva,clientes,reservas);
            pagarReserva(numReserva,reservas,habitaciones,precios);
            fprintf(archivo, "Reserva pagada:\nNúmero de Reserva: %d\nCliente: %s\nCédula: %s\nHabitación: %s\nTipo de Habitación: %s\nHotel: %s\nPrecio: %.2f\n\n",
                    numReserva, clientes[reservas[numReserva][1]][0], clientes[reservas[numReserva][1]][1],
                    habitaciones[reservas[numReserva][2]][0], habitaciones[reservas[numReserva][2]][1], 
                    habitaciones[reservas[numReserva][2]][2], precios[reservas[numReserva][2]]);
            break;
        default:
            break;
        }
        printf("Desea elegir otra opcion\n>>");
        scanf("%d",&opcion);
    } while (opcion==1);
    
    fclose(archivo); // Cerrar el archivo al finalizar el programa

 return 0; 
}