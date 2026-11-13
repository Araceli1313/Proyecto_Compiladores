
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "codegen_f1.h"

/* Escribir espacios de indentacion */
static void generate_indent(FILE *out, int indent_level) {
    for (int i = 0; i < indent_level; i++) {
        fprintf(out, "    ");
    }
}

/* Buscar si una variable recibe una cadena de texto */
static int variable_recibe_cadena(ASTNode *node, const char *nombre) {

    if (!node || !nombre) {
        return 0;
    }

    if (node->tipo == AST_ASIGNACION &&
        node->izquierda &&
        node->izquierda->valor &&
        strcmp(node->izquierda->valor, nombre) == 0 &&
        node->derecha &&
        node->derecha->tipo == AST_CADENA) {

        return 1;
    }

    if (variable_recibe_cadena(node->izquierda, nombre)) {
        return 1;
    }

    if (variable_recibe_cadena(node->derecha, nombre)) {
        return 1;
    }

    if (variable_recibe_cadena(node->tercero, nombre)) {
        return 1;
    }

    return 0;
}

/* Procesar y escribir expresiones */
static void generate_expression(ASTNode *node, FILE *out) {

    if (!node) {
        return;
    }

    switch (node->tipo) {

        case AST_NUMERO:
        case AST_IDENTIFICADOR:
        case AST_CADENA:

            if (node->valor) {
                fprintf(out, "%s", node->valor);
            }

            break;

        case AST_OPERACION:

            fprintf(out, "(");

            generate_expression(node->izquierda, out);

            if (node->valor) {
                fprintf(out, " %s ", node->valor);
            }

            generate_expression(node->derecha, out);

            fprintf(out, ")");

            break;

        case AST_COMPARACION:

            generate_expression(node->izquierda, out);

            if (node->valor) {
                fprintf(out, " %s ", node->valor);
            }

            generate_expression(node->derecha, out);

            break;

        default:
            break;
    }
}

/* Procesar y escribir instrucciones */
static void generate_statement(
    ASTNode *node,
    ASTNode *root,
    FILE *out,
    int indent_level
) {

    if (!node) {
        return;
    }

    switch (node->tipo) {

        case AST_PROGRAMA:
        case AST_BLOQUE:

            generate_statement(node->izquierda, root, out, indent_level);
            generate_statement(node->derecha, root, out, indent_level);

            break;

        /* Declaraciones */

        case AST_DECLARACION:

            generate_indent(out, indent_level);

            if (node->izquierda && node->izquierda->valor) {

                const char *nombre = node->izquierda->valor;

                if (variable_recibe_cadena(root, nombre)) {

                    fprintf(out, "garage pilot %s := \"\";\n", nombre);
                }
                else if (node->valor &&
                         strcmp(node->valor, "ipint") == 0) {

                    fprintf(out, "garage engine %s := 0;\n", nombre);
                }
                else if (node->valor &&
                         (strcmp(node->valor, "ipfloat") == 0 ||
                          strcmp(node->valor, "repealpa") == 0)) {

                    fprintf(out, "garage fuel %s := 0.0;\n", nombre);
                }
            }

            break;

        /* Asignaciones */

        case AST_ASIGNACION:

            generate_indent(out, indent_level);

            if (node->izquierda && node->izquierda->valor) {
                fprintf(out, "%s := ", node->izquierda->valor);
            }

            generate_expression(node->derecha, out);

            fprintf(out, ";\n");

            break;

        /* Entrada */

        case AST_ENTRADA:

            generate_indent(out, indent_level);

            if (node->izquierda && node->izquierda->valor) {
                fprintf(out, "pitstop %s;\n", node->izquierda->valor);
            }

            break;

        /* Salida */

        case AST_SALIDA:

            generate_indent(out, indent_level);

            fprintf(out, "radio ");

            if (node->izquierda) {
                generate_expression(node->izquierda, out);
            }

            fprintf(out, ";\n");

            break;

        /* Comentarios de una línea y multilinea */

        case AST_COMENTARIO:

            generate_indent(out, indent_level);

            if (node->valor) {
                fprintf(out, "%s\n", node->valor);
            }

            break;

        /* Condicionales */

        case AST_CONDICIONAL:

            generate_indent(out, indent_level);

            fprintf(out, "race (");

            generate_expression(node->izquierda, out);

            fprintf(out, ") {\n");

            generate_statement(
                node->derecha,
                root,
                out,
                indent_level + 1
            );

            generate_indent(out, indent_level);

            fprintf(out, "}\n");

            /* Rama alternativa */

            if (node->tercero) {

                generate_indent(out, indent_level);

                if (node->tercero->tipo == AST_CONDICIONAL) {

                    fprintf(out, "overtake ");

                    generate_statement(
                        node->tercero,
                        root,
                        out,
                        indent_level
                    );
                }
                else {

                    fprintf(out, "overtake {\n");

                    generate_statement(
                        node->tercero,
                        root,
                        out,
                        indent_level + 1
                    );

                    generate_indent(out, indent_level);

                    fprintf(out, "}\n");
                }
            }

            break;

        /* Ciclo mientras */

        case AST_CICLO:

            generate_indent(out, indent_level);

            fprintf(out, "lap (");

            generate_expression(node->izquierda, out);

            fprintf(out, ") {\n");

            generate_statement(
                node->derecha,
                root,
                out,
                indent_level + 1
            );

            generate_indent(out, indent_level);

            fprintf(out, "}\n");

            break;

        default:
            break;
    }
}

/* Generar el archivo F1Code */

void generate_f1code(
    ASTNode *root,
    const char *output_filename
) {

    FILE *out = fopen(output_filename, "w");

    if (!out) {
        perror("Error al crear el archivo F1Code.f1");
        return;
    }

    fprintf(out, "// Traduccion automatica de Dara a F1Code (.f1)\n\n");

    generate_statement(root, root, out, 0);

    fprintf(out, "\nfinish;\n");

    fclose(out);

    printf("[OK] Archivo generado exitosamente: %s\n", output_filename);
}
