#include <stdio.h>
#include <string.h>
#include "funciones.h"

void buscarPorTamano(int *numHabitacion, char habitaciones[9][3][40], double precios[9]) {
    char tipo[20];
    printf("Ingrese el tipo de habitacion (simple, doble, triple): ");
    scanf("%s", tipo);
    for (int i = 0; i < 9; i++) {
        if (strcmp(habitaciones[i][1], tipo) == 0) {
            printf("Habitacion %s en %s cuesta %.2f\n", habitaciones[i][0], habitaciones[i][2], precios[i]);
        }
    }
    printf("Ingrese el numero de habitacion que desea: ");
    scanf("%d", numHabitacion);
}

void buscarHotel(int *numHabitacion, char habitaciones[9][3][40], double precios[9]) {
    char hotel[40];
    printf("Ingrese el nombre del hotel: ");
    scanf("%s", hotel);

    printf("Habitaciones disponibles en %s:\n", hotel);
    int found = 0;  // Bandera para verificar si se encontró alguna habitación
    for (int i = 0; i < 9; i++) {
        if (strcmp(habitaciones[i][2], hotel) == 0) {
            printf("Habitacion %s (%s) cuesta %.2f\n", habitaciones[i][0], habitaciones[i][1], precios[i]);
            found = 1;
        }
    }

    if (found) {
        printf("Ingrese el numero de habitacion que desea: ");
        scanf("%d", numHabitacion);
    } else {
        printf("No se encontraron habitaciones disponibles en el hotel %s.\n", hotel);
        *numHabitacion = -1;  // Valor inválido para indicar que no se encontró ninguna habitación
    }
}

void realizarReserva(int numHabitacion, char habitaciones[9][3][40], char clientes[5][2][40], int reservas[10][4], double precios[9]) {
    if (numHabitacion < 1 || numHabitacion > 9) {
        printf("Número de habitación inválido.\n");
        return;
    }

    char nombre[40];
    char cedula[40];

    printf("Ingresa tu nombre: ");
    scanf("%s", nombre);
    printf("Ingresa tu cédula: ");
    scanf("%s", cedula);

    // Buscar un espacio vacío para la reserva
    for (int i = 0; i < 10; i++) {
        if (reservas[i][0] == -1) {
            reservas[i][0] = numHabitacion;
            strcpy(clientes[i][0], nombre);
            strcpy(clientes[i][1], cedula);
            reservas[i][1] = i;  // Número de reserva
            reservas[i][2] = 0;  // Inicialmente no pagada
            reservas[i][3] = 1;  // Reserva activa

            printf("Reserva realizada con éxito.\n");
            printf("Detalle de la reserva:\n");
            printf("Cliente: %s\n", nombre);
            printf("Cédula: %s\n", cedula);
            printf("Habitación: %s (%s) en %s\n", habitaciones[numHabitacion - 1][0], habitaciones[numHabitacion - 1][1], habitaciones[numHabitacion - 1][2]);
            printf("Precio: %.2f\n", precios[numHabitacion - 1]);

            return;
        }
    }

    printf("No se pudo realizar la reserva, todas las reservas están ocupadas.\n");
}

void buscarReservaPorCedula(int *numReserva, char clientes[5][2][40], int reservas[10][4]) {
    char cedula[40];
    printf("Ingresa tu cédula: ");
    scanf("%s", cedula);

    for (int i = 0; i < 5; i++) {
        if (strcmp(clientes[i][1], cedula) == 0) {
            *numReserva = reservas[i][1];
            printf("Reserva encontrada para %s con cédula %s.\n", clientes[i][0], cedula);
            return;
        }
    }

    *numReserva = -1; // No se encontró reserva
    printf("No se encontró ninguna reserva con esa cédula.\n");
}

void imprimirReserva(int numReserva, int reservas[10][4], char habitaciones[9][3][40], double precios[9]) {
    if (numReserva == -1 || reservas[numReserva][0] == -1) {
        printf("Reserva no encontrada.\n");
        return;
    }

    int numHabitacion = reservas[numReserva][0];
    printf("Detalle de la Reserva:\n");
    printf("Número de Reserva: %d\n", numReserva);
    printf("Habitación: %s\n", habitaciones[numHabitacion - 1][0]);
    printf("Tipo de Habitación: %s\n", habitaciones[numHabitacion - 1][1]);
    printf("Hotel: %s\n", habitaciones[numHabitacion - 1][2]);
    printf("Precio: %.2f\n", precios[numHabitacion - 1]);

    if (reservas[numReserva][3] == 1) {
        printf("Estado: Activa\n");
    } else {
        printf("Estado: Pagada\n");
    }
}

void pagarReserva(int numReserva, int reservas[10][4], char habitaciones[9][3][40], double precios[9]) {
    if (numReserva == -1 || reservas[numReserva][0] == -1) {
        printf("Reserva no encontrada.\n");
        return;
    }

    int numHabitacion = reservas[numReserva][0];
    printf("Detalles de la reserva:\n");
    printf("Número de Reserva: %d\n", numReserva);
    printf("Habitación: %s\n", habitaciones[numHabitacion - 1][0]);
    printf("Tipo de Habitación: %s\n", habitaciones[numHabitacion - 1][1]);
    printf("Hotel: %s\n", habitaciones[numHabitacion - 1][2]);
    printf("Precio: %.2f\n", precios[numHabitacion - 1]);

    if (reservas[numReserva][3] == 0) {
        printf("La reserva ya ha sido pagada.\n");
        return;
    }

    printf("¿Desea pagar esta reserva? (1 para sí, 0 para no): ");
    int confirmacion;
    scanf("%d", &confirmacion);

    if (confirmacion == 1) {
        reservas[numReserva][3] = 0; // Marcar como pagada
        printf("Reserva pagada con éxito.\n");
    } else {
        printf("Pago cancelado.\n");
    }
}
