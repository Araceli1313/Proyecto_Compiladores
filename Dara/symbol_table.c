#include <stdio.h>
#include <string.h>

#include "symbol_table.h"

static Simbolo tabla[MAX_SIMBOLOS];
static int cantidad_simbolos = 0;

/* Agregar una variable a la tabla */
int tabla_agregar(const char *nombre, const char *tipo) {

    if (tabla_existe(nombre)) {
        fprintf(stderr,
                "Error: la variable '%s' ya fue declarada.\n",
                nombre);
        return 0;
    }

    if (cantidad_simbolos >= MAX_SIMBOLOS) {
        fprintf(stderr,
                "Error: se alcanzo el maximo de simbolos.\n");
        return 0;
    }

    strncpy(
        tabla[cantidad_simbolos].nombre,
        nombre,
        sizeof(tabla[cantidad_simbolos].nombre) - 1
    );

    tabla[cantidad_simbolos].nombre[
        sizeof(tabla[cantidad_simbolos].nombre) - 1
    ] = '\0';

    strncpy(
        tabla[cantidad_simbolos].tipo,
        tipo,
        sizeof(tabla[cantidad_simbolos].tipo) - 1
    );

    tabla[cantidad_simbolos].tipo[
        sizeof(tabla[cantidad_simbolos].tipo) - 1
    ] = '\0';

    cantidad_simbolos++;

    return 1;
}

/* Verificar si una variable existe */
int tabla_existe(const char *nombre) {

    for (int i = 0; i < cantidad_simbolos; i++) {

        if (strcmp(tabla[i].nombre, nombre) == 0) {
            return 1;
        }
    }

    return 0;
}

/* Mostrar la tabla de simbolos */
void tabla_imprimir(void) {

    if (cantidad_simbolos == 0) {
        printf("(tabla vacia)\n");
        return;
    }

    printf("%-20s %-20s\n", "NOMBRE", "TIPO");
    printf("----------------------------------------\n");

    for (int i = 0; i < cantidad_simbolos; i++) {

        printf(
            "%-20s %-20s\n",
            tabla[i].nombre,
            tabla[i].tipo
        );
    }
}

/* Vaciar la tabla */
void tabla_limpiar(void) {
    cantidad_simbolos = 0;
}