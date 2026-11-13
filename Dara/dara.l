
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "dara.tab.h"

extern int yylineno;
%}

%option noyywrap
%option yylineno

%%

"nepew"     { return NEPEW; }
"ipint"     { return IPINT; }
"ipfloat"   { return IPFLOAT; }
"repealpa"  { return REPEALPA; }
"repeapad"  { return REPEAPAD; }
"pripint"   { return PRIPINT; }
"ipif"      { return IPIF; }
"epelsepe"  { return EPELSEPE; }
"whipilepe" { return WHIPILEPE; }

"<-"        { return ASIGNACION; }

"=="        { return IGUAL; }
"!="        { return DIFERENTE; }
"<="        { return MENOR_IGUAL; }
">="        { return MAYOR_IGUAL; }
"<"         { return MENOR; }
">"         { return MAYOR; }

"+"         { return MAS; }
"-"         { return MENOS; }
"*"         { return POR; }
"/"         { return DIVISION; }

";"         { return PUNTO_COMA; }
"{"         { return LLAVE_ABRE; }
"}"         { return LLAVE_CIERRA; }
"("         { return PARENTESIS_ABRE; }
")"         { return PARENTESIS_CIERRA; }

"/*"([^*]|\*+[^*/])*\*+"/" {
    yylval.text = strdup(yytext);
    return COMENTARIO;
}

"//"[^\r\n]* {
    yylval.text = strdup(yytext);
    return COMENTARIO;
}

\"([^\"\\\n]|\\.)*\" {
    yylval.text = strdup(yytext);
    return CADENA;
}

[0-9]+\.[0-9]+ {
    yylval.text = strdup(yytext);
    return NUMERO_REAL;
}

[0-9]+ {
    yylval.text = strdup(yytext);
    return NUMERO_ENTERO;
}

[a-zA-Z][a-zA-Z0-9_]* {
    yylval.text = strdup(yytext);
    return IDENTIFICADOR;
}

[ \t\r\n]+ {
}

. {
    printf("[Error Lexico] Caracter no reconocido: '%s' en la linea %d\n",
           yytext, yylineno);
    return ERROR_LEXICO;
}

%%

