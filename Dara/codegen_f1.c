#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "codegen_f1.h"

/* Función auxiliar para procesar y escribir expresiones */
static void generate_expression(ASTNode *node, FILE *out) {
    if (!node) return;

    switch (node->tipo) {
        case AST_NUMERO:
        case AST_IDENTIFICADOR:
            if (node->valor) {
                fprintf(out, "%s", node->valor);
            }
            break;

        case AST_OPERACION:
            /* Mantener paréntesis en operaciones aritméticas */
            fprintf(out, "(");
            generate_expression(node->izquierda, out);
            if (node->valor) {
                fprintf(out, " %s ", node->valor);
            }

            generate_expression(node->derecha, out);
            fprintf(out, ")");
            break;

        case AST_COMPARACION:
            /* No agregar paréntesis externos a la comparación */
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

/* Función auxiliar para procesar instrucciones y sentencias */
static void generate_statement(ASTNode *node, FILE *out, int indent_level) {
    if (!node) return;

    switch (node->tipo) {
        case AST_PROGRAMA:
        case AST_BLOQUE:
            generate_statement(node->izquierda, out, indent_level);
            generate_statement(node->derecha, out, indent_level);
            break;

        case AST_DECLARACION:
            for (int i = 0; i < indent_level; i++) {
                fprintf(out, "    ");
            }

            /* ipint -> garage engine */
            if (node->valor && strcmp(node->valor, "ipint") == 0) {
                fprintf(out, "garage engine ");

                if (node->izquierda && node->izquierda->valor) {
                    fprintf(out, "%s := 0;\n",
                            node->izquierda->valor);
                }
            }
            /* ipfloat -> garage fuel */
            else if (node->valor &&
                     strcmp(node->valor, "ipfloat") == 0) {
                fprintf(out, "garage fuel ");

                if (node->izquierda && node->izquierda->valor) {
                    fprintf(out, "%s := 0.0;\n",
                            node->izquierda->valor);
                }
            }
            /* repealpa -> garage fuel */
            else {
                fprintf(out, "garage fuel ");

                if (node->izquierda && node->izquierda->valor) {
                    fprintf(out, "%s := 0.0;\n",
                            node->izquierda->valor);
                }
            }
            break;

        case AST_ASIGNACION:
            for (int i = 0; i < indent_level; i++) {
                fprintf(out, "    ");
            }

            if (node->izquierda && node->izquierda->valor) {
                fprintf(out, "%s := ", node->izquierda->valor);
            } else if (node->izquierda &&
                       node->izquierda->izquierda &&
                       node->izquierda->izquierda->valor) {
                fprintf(out, "%s := ",
                        node->izquierda->izquierda->valor);
            }

            generate_expression(node->derecha, out);
            fprintf(out, ";\n");
            break;

        case AST_ENTRADA:
            for (int i = 0; i < indent_level; i++) {
                fprintf(out, "    ");
            }

            if (node->izquierda && node->izquierda->valor) {
                fprintf(out, "pitstop %s;\n",
                        node->izquierda->valor);
            }
            break;

        case AST_SALIDA:
            for (int i = 0; i < indent_level; i++) {
                fprintf(out, "    ");
            }

            fprintf(out, "radio ");

            if (node->izquierda) {
                generate_expression(node->izquierda, out);
            } else if (node->valor) {
                fprintf(out, "%s", node->valor);
            }

            fprintf(out, ";\n");
            break;

        case AST_CONDICIONAL:
            for (int i = 0; i < indent_level; i++) {
                fprintf(out, "    ");
            }

            fprintf(out, "race (");
            generate_expression(node->izquierda, out);
            fprintf(out, ") {\n");

            generate_statement(node->derecha, out, indent_level + 1);

            if (node->tercero) {
                for (int i = 0; i < indent_level; i++) {
                    fprintf(out, "    ");
                }

                fprintf(out, "} overtake {\n");
                generate_statement(node->tercero, out,
                                   indent_level + 1);
            }

            for (int i = 0; i < indent_level; i++) {
                fprintf(out, "    ");
            }

            fprintf(out, "}\n");
            break;

        case AST_CICLO:
            for (int i = 0; i < indent_level; i++) {
                fprintf(out, "    ");
            }

            fprintf(out, "lap (");
            generate_expression(node->izquierda, out);
            fprintf(out, ") {\n");

            generate_statement(node->derecha, out, indent_level + 1);

            for (int i = 0; i < indent_level; i++) {
                fprintf(out, "    ");
            }

            fprintf(out, "}\n");
            break;

        default:
            break;
    }
}

/* Función principal para generar el archivo .f1 */
void generate_f1code(ASTNode *root, const char *output_filename) {
    FILE *out = fopen(output_filename, "w");

    if (!out) {
        perror("Error al crear el archivo F1Code.f1");
        return;
    }

    fprintf(out,
            "// Traduccion automatica de Dara a F1Code (.f1)\n\n");

    generate_statement(root, out, 0);

    fprintf(out, "\nfinish;\n");

    fclose(out);

    printf("[OK] Archivo generado exitosamente: %s\n",
           output_filename);
}