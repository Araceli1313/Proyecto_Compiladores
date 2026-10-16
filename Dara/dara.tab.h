/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_DARA_TAB_H_INCLUDED
# define YY_YY_DARA_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 20 "dara.y"

#include "ast.h"

#line 53 "dara.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NEPEW = 258,                   /* NEPEW  */
    IPINT = 259,                   /* IPINT  */
    IPFLOAT = 260,                 /* IPFLOAT  */
    REPEALPA = 261,                /* REPEALPA  */
    REPEAPAD = 262,                /* REPEAPAD  */
    PRIPINT = 263,                 /* PRIPINT  */
    IPIF = 264,                    /* IPIF  */
    EPELSEPE = 265,                /* EPELSEPE  */
    WHIPILEPE = 266,               /* WHIPILEPE  */
    ASIGNACION = 267,              /* ASIGNACION  */
    MENOR = 268,                   /* MENOR  */
    MAYOR = 269,                   /* MAYOR  */
    MENOR_IGUAL = 270,             /* MENOR_IGUAL  */
    MAYOR_IGUAL = 271,             /* MAYOR_IGUAL  */
    IGUAL = 272,                   /* IGUAL  */
    DIFERENTE = 273,               /* DIFERENTE  */
    MAS = 274,                     /* MAS  */
    MENOS = 275,                   /* MENOS  */
    POR = 276,                     /* POR  */
    DIVISION = 277,                /* DIVISION  */
    PUNTO_COMA = 278,              /* PUNTO_COMA  */
    LLAVE_ABRE = 279,              /* LLAVE_ABRE  */
    LLAVE_CIERRA = 280,            /* LLAVE_CIERRA  */
    PARENTESIS_ABRE = 281,         /* PARENTESIS_ABRE  */
    PARENTESIS_CIERRA = 282,       /* PARENTESIS_CIERRA  */
    IDENTIFICADOR = 283,           /* IDENTIFICADOR  */
    NUMERO_ENTERO = 284,           /* NUMERO_ENTERO  */
    NUMERO_REAL = 285,             /* NUMERO_REAL  */
    ERROR_LEXICO = 286             /* ERROR_LEXICO  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 24 "dara.y"

    char *text;
    ASTNode *node;

#line 106 "dara.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_DARA_TAB_H_INCLUDED  */
