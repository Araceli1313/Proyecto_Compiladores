#ifndef CODEGEN_F1_H
#define CODEGEN_F1_H

#include <stdio.h>
#include "ast.h"

/* Función principal para traducir el AST de Dara a F1Code (.f1) */
void generate_f1code(ASTNode *root, const char *output_filename);

#endif // CODEGEN_F1_H