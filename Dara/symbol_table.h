#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define MAX_SIMBOLOS 100

typedef struct {
    char nombre[100];
    char tipo[20];
} Simbolo;

/* Agregar una variable a la tabla */
int tabla_agregar(const char *nombre, const char *tipo);

/* Verificar si una variable existe */
int tabla_existe(const char *nombre);

/* Mostrar la tabla de símbolos */
void tabla_imprimir(void);

/* Vaciar la tabla */
void tabla_limpiar(void);

#endif