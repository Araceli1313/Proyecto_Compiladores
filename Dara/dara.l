%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "dara.tab.h"
%}

%option noyywrap
%option yylineno

%%

"nepew"         { return NEPEW; }
"ipint"         { return IPINT; }
"repealpa"      { return REPEALPA; }
"repeapad"      { return REPEAPAD; }
"pripint"       { return PRIPINT; }
"ipif"          { return IPIF; }
"epelsepe"      { return EPELSEPE; }
"whipilepe"     { return WHIPILEPE; }

"<-"            { return ASIGNACION; }

"<="            { return MENOR_IGUAL; }
">="            { return MAYOR_IGUAL; }
"=="            { return IGUAL; }
"!="            { return DIFERENTE; }
"<"             { return MENOR; }
">"             { return MAYOR; }

"+"             { return MAS; }
"-"             { return MENOS; }
"*"             { return POR; }
"/"             { return DIVISION; }

";"             { return PUNTO_COMA; }
"{"             { return LLAVE_ABRE; }
"}"             { return LLAVE_CIERRA; }
"("             { return PARENTESIS_ABRE; }
")"             { return PARENTESIS_CIERRA; }

[0-9]+\.[0-9]+  { yylval.text = strdup(yytext); return NUMERO_REAL; }
[0-9]+          { yylval.text = strdup(yytext); return NUMERO_ENTERO; }
[a-zA-Z][a-zA-Z0-9_]* { yylval.text = strdup(yytext); return IDENTIFICADOR; }

"//".*          { /* Ignorar comentarios de una línea */ }
"/*"([^*]|\*+[^/*])*\*+"/" { /* Ignorar comentarios multilínea */ }
[ \t\r\n]+      { /* Ignorar espacios en blanco */ }

.               { return ERROR_LEXICO; }

%%
