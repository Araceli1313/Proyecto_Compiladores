%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "symbol_table.h"

int yylex(void);
void yyerror(const char *mensaje);
extern FILE *yyin;

ASTNode *raiz = NULL;
int hubo_error = 0;
%}

%code requires {
#include "ast.h"
}

%union {
    char *text;
    ASTNode *node;
}

%token NEPEW
%token IPINT
%token REPEALPA
%token REPEAPAD
%token PRIPINT
%token IPIF
%token EPELSEPE
%token WHIPILEPE

%token ASIGNACION

%token MENOR
%token MAYOR
%token MENOR_IGUAL
%token MAYOR_IGUAL
%token IGUAL
%token DIFERENTE

%token MAS
%token MENOS
%token POR
%token DIVISION

%token PUNTO_COMA
%token LLAVE_ABRE
%token LLAVE_CIERRA
%token PARENTESIS_ABRE
%token PARENTESIS_CIERRA

%token <text> IDENTIFICADOR
%token <text> NUMERO_ENTERO
%token <text> NUMERO_REAL

%token ERROR_LEXICO
%left MAS MENOS
%left POR DIVISION

%type <node> programa
%type <node> instrucciones
%type <node> instruccion
%type <node> bloque
%type <node> declaracion
%type <node> asignacion
%type <node> entrada
%type <node> salida
%type <node> condicional
%type <node> ciclo
%type <node> condicion
%type <node> expresion
%type <node> termino
%type <node> factor

%type <text> tipo
%type <text> operador_comparacion
%%
programa
    : instrucciones
      {
          raiz = $1;
      }
    ;
instrucciones
    : instruccion instrucciones
      {
          $$ = ast_crear_bloque($1, $2);
      }
    | /* vacío */
      {
          $$ = NULL;
      }
    ;
instruccion
    : declaracion
      { $$ = $1; }
    | asignacion
      { $$ = $1; }
    | entrada
      { $$ = $1; }
    | salida
      { $$ = $1; }
    | condicional
      { $$ = $1; }
    | ciclo
      { $$ = $1; }
    ;
declaracion
    : NEPEW tipo IDENTIFICADOR PUNTO_COMA
      {
          tabla_agregar($3, $2);
          $$ = ast_crear_declaracion($2, $3);
      }
    ;
tipo
    : IPINT
      {
          $$ = strdup("ipint");
      }
    | REPEALPA
      {
          $$ = strdup("repealpa");
      }
    ;
asignacion
    : IDENTIFICADOR ASIGNACION expresion PUNTO_COMA
      {
          if (!tabla_existe($1)) {
              fprintf(stderr,
                      "Error: la variable '%s' no ha sido declarada.\n",
                      $1);
              hubo_error = 1;
          }

          $$ = ast_crear_asignacion($1, $3);
      }
    ;
entrada
    : REPEAPAD IDENTIFICADOR PUNTO_COMA
      {
          if (!tabla_existe($2)) {
              fprintf(stderr,
                      "Error: la variable '%s' no ha sido declarada.\n",
                      $2);
              hubo_error = 1;
          }

          $$ = ast_crear_entrada($2);
      }
    ;
salida
    : PRIPINT IDENTIFICADOR PUNTO_COMA
      {
          if (!tabla_existe($2)) {
              fprintf(stderr,
                      "Error: la variable '%s' no ha sido declarada.\n",
                      $2);
              hubo_error = 1;
          }

          $$ = ast_crear_salida($2);
      }
    ;
condicional
    : IPIF condicion bloque EPELSEPE bloque
      {
          $$ = ast_crear_condicional($2, $3, $5);
      }
    ;
ciclo
    : WHIPILEPE condicion bloque
      {
          $$ = ast_crear_ciclo($2, $3);
      }
    ;
bloque
    : LLAVE_ABRE instrucciones LLAVE_CIERRA
      {
          $$ = $2;
      }
    ;
condicion
    : expresion operador_comparacion expresion
      {
          $$ = ast_crear_comparacion($2, $1, $3);
      }
    ;
operador_comparacion
    : MENOR
      { $$ = strdup("<"); }
    | MAYOR
      { $$ = strdup(">"); }
    | MENOR_IGUAL
      { $$ = strdup("<="); }
    | MAYOR_IGUAL
      { $$ = strdup(">="); }
    | IGUAL
      { $$ = strdup("=="); }
    | DIFERENTE
      { $$ = strdup("!="); }
    ;
expresion
    : expresion MAS termino
      {
          $$ = ast_crear_operacion("+", $1, $3);
      }
    | expresion MENOS termino
      {
          $$ = ast_crear_operacion("-", $1, $3);
      }
    | termino
      {
          $$ = $1;
      }
    ;
termino
    : termino POR factor
      {
          $$ = ast_crear_operacion("*", $1, $3);
      }
    | termino DIVISION factor
      {
          $$ = ast_crear_operacion("/", $1, $3);
      }
    | factor
      {
          $$ = $1;
      }
    ;
factor
    : IDENTIFICADOR
      {
          if (!tabla_existe($1)) {
              fprintf(stderr,
                      "Error: la variable '%s' no ha sido declarada.\n",
                      $1);
              hubo_error = 1;
          }

          $$ = ast_crear_identificador($1);
      }
    | NUMERO_ENTERO
      {
          $$ = ast_crear_numero($1);
      }
    | NUMERO_REAL
      {
          $$ = ast_crear_numero($1);
      }
    | PARENTESIS_ABRE expresion PARENTESIS_CIERRA
      {
          $$ = $2;
      }
    ;
%%
void yyerror(const char *mensaje) {
    fprintf(stderr, "Error de sintaxis: %s\n", mensaje);
    hubo_error = 1;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s archivo.da\n", argv[0]);
        return 1;
    }

    FILE *archivo = fopen(argv[1], "r");

    if (!archivo) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    yyin = archivo;

    int resultado = yyparse();

    fclose(archivo);

    if (resultado == 0 && !hubo_error) {
        printf("\n=== AST ===\n");
        ast_imprimir(raiz, 0);

        printf("\n=== TABLA DE SIMBOLOS ===\n");
        tabla_imprimir();

        printf("\nPrograma valido.\n");

        return 0;
    }

    printf("\nPrograma invalido.\n");

    return 1;
}