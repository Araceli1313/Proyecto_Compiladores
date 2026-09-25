#ifndef AST_H
#define AST_H

typedef struct ASTNode ASTNode;

typedef enum {
    AST_PROGRAMA,
    AST_BLOQUE,
    AST_DECLARACION,
    AST_ASIGNACION,
    AST_ENTRADA,
    AST_SALIDA,
    AST_CONDICIONAL,
    AST_CICLO,
    AST_COMPARACION,
    AST_OPERACION,
    AST_IDENTIFICADOR,
    AST_NUMERO
} ASTNodeType;

struct ASTNode {
    ASTNodeType tipo;

    char *valor;

    ASTNode *izquierda;
    ASTNode *derecha;
    ASTNode *tercero;
};

/* Funciones para crear nodos */
ASTNode *ast_crear_bloque(ASTNode *instruccion, ASTNode *siguiente);
ASTNode *ast_crear_declaracion(const char *tipo, const char *identificador);
ASTNode *ast_crear_asignacion(const char *identificador, ASTNode *expresion);
ASTNode *ast_crear_entrada(const char *identificador);
ASTNode *ast_crear_salida(const char *identificador);
ASTNode *ast_crear_condicional(ASTNode *condicion, ASTNode *bloque_if, ASTNode *bloque_else);
ASTNode *ast_crear_ciclo(ASTNode *condicion, ASTNode *bloque);
ASTNode *ast_crear_comparacion(const char *operador, ASTNode *izquierda, ASTNode *derecha);
ASTNode *ast_crear_operacion(const char *operador, ASTNode *izquierda, ASTNode *derecha);
ASTNode *ast_crear_identificador(const char *nombre);
ASTNode *ast_crear_numero(const char *valor);

/* Función para mostrar el AST */
void ast_imprimir(ASTNode *nodo, int nivel);

/* Liberar memoria del AST */
void ast_liberar(ASTNode *nodo);

#endif