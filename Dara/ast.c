#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"

/* Crear un nodo básico */
static ASTNode *ast_crear_nodo(ASTNodeType tipo, const char *valor) {
    ASTNode *nodo = malloc(sizeof(ASTNode));

    if (nodo == NULL) {
        fprintf(stderr, "Error: no se pudo reservar memoria para el AST.\n");
        exit(EXIT_FAILURE);
    }

    nodo->tipo = tipo;

    if (valor != NULL) {
        nodo->valor = strdup(valor);
    } else {
        nodo->valor = NULL;
    }

    nodo->izquierda = NULL;
    nodo->derecha = NULL;
    nodo->tercero = NULL;

    return nodo;
}

/* Crear un bloque de instrucciones */
ASTNode *ast_crear_bloque(ASTNode *instruccion, ASTNode *siguiente) {
    ASTNode *nodo = ast_crear_nodo(AST_BLOQUE, NULL);

    nodo->izquierda = instruccion;
    nodo->derecha = siguiente;

    return nodo;
}

/* Crear declaración */
ASTNode *ast_crear_declaracion(const char *tipo, const char *identificador) {
    ASTNode *nodo = ast_crear_nodo(AST_DECLARACION, tipo);

    nodo->izquierda = ast_crear_identificador(identificador);

    return nodo;
}

/* Crear asignación */
ASTNode *ast_crear_asignacion(const char *identificador, ASTNode *expresion) {
    ASTNode *nodo = ast_crear_nodo(AST_ASIGNACION, "<-");

    nodo->izquierda = ast_crear_identificador(identificador);
    nodo->derecha = expresion;

    return nodo;
}

/* Crear entrada */
ASTNode *ast_crear_entrada(const char *identificador) {
    ASTNode *nodo = ast_crear_nodo(AST_ENTRADA, "repeapad");

    nodo->izquierda = ast_crear_identificador(identificador);

    return nodo;
}

/* Crear salida */
ASTNode *ast_crear_salida(const char *identificador) {
    ASTNode *nodo = ast_crear_nodo(AST_SALIDA, "pripint");

    nodo->izquierda = ast_crear_identificador(identificador);

    return nodo;
}

/* Crear condicional */
ASTNode *ast_crear_condicional(
    ASTNode *condicion,
    ASTNode *bloque_if,
    ASTNode *bloque_else
) {
    ASTNode *nodo = ast_crear_nodo(AST_CONDICIONAL, "ipif");

    nodo->izquierda = condicion;
    nodo->derecha = bloque_if;
    nodo->tercero = bloque_else;

    return nodo;
}

/* Crear ciclo */
ASTNode *ast_crear_ciclo(
    ASTNode *condicion,
    ASTNode *bloque
) {
    ASTNode *nodo = ast_crear_nodo(AST_CICLO, "whipilepe");

    nodo->izquierda = condicion;
    nodo->derecha = bloque;

    return nodo;
}

/* Crear comparación */
ASTNode *ast_crear_comparacion(
    const char *operador,
    ASTNode *izquierda,
    ASTNode *derecha
) {
    ASTNode *nodo = ast_crear_nodo(AST_COMPARACION, operador);

    nodo->izquierda = izquierda;
    nodo->derecha = derecha;

    return nodo;
}

/* Crear operación aritmética */
ASTNode *ast_crear_operacion(
    const char *operador,
    ASTNode *izquierda,
    ASTNode *derecha
) {
    ASTNode *nodo = ast_crear_nodo(AST_OPERACION, operador);

    nodo->izquierda = izquierda;
    nodo->derecha = derecha;

    return nodo;
}

/* Crear identificador */
ASTNode *ast_crear_identificador(const char *nombre) {
    return ast_crear_nodo(AST_IDENTIFICADOR, nombre);
}

/* Crear número */
ASTNode *ast_crear_numero(const char *valor) {
    return ast_crear_nodo(AST_NUMERO, valor);
}

/* Obtener nombre del tipo de nodo */
static const char *ast_nombre_tipo(ASTNodeType tipo) {
    switch (tipo) {
        case AST_PROGRAMA:
            return "PROGRAMA";

        case AST_BLOQUE:
            return "BLOQUE";

        case AST_DECLARACION:
            return "DECLARACION";

        case AST_ASIGNACION:
            return "ASIGNACION";

        case AST_ENTRADA:
            return "ENTRADA";

        case AST_SALIDA:
            return "SALIDA";

        case AST_CONDICIONAL:
            return "CONDICIONAL";

        case AST_CICLO:
            return "CICLO";

        case AST_COMPARACION:
            return "COMPARACION";

        case AST_OPERACION:
            return "OPERACION";

        case AST_IDENTIFICADOR:
            return "IDENTIFICADOR";

        case AST_NUMERO:
            return "NUMERO";

        default:
            return "DESCONOCIDO";
    }
}

/* Imprimir AST */
void ast_imprimir(ASTNode *nodo, int nivel) {
    if (nodo == NULL) {
        return;
    }

    for (int i = 0; i < nivel; i++) {
        printf("  ");
    }

    printf("%s", ast_nombre_tipo(nodo->tipo));

    if (nodo->valor != NULL) {
        printf(": %s", nodo->valor);
    }

    printf("\n");

    ast_imprimir(nodo->izquierda, nivel + 1);
    ast_imprimir(nodo->derecha, nivel + 1);
    ast_imprimir(nodo->tercero, nivel + 1);
}

/* Liberar memoria del AST */
void ast_liberar(ASTNode *nodo) {
    if (nodo == NULL) {
        return;
    }

    ast_liberar(nodo->izquierda);
    ast_liberar(nodo->derecha);
    ast_liberar(nodo->tercero);

    free(nodo->valor);
    free(nodo);
}