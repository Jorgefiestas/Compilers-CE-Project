/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     NUM = 259,
     INT = 260,
     VOID = 261,
     RETORNO = 262,
     SI = 263,
     SINO = 264,
     MIENTRAS = 265,
     ASSIGN = 266,
     MULOP = 267,
     DIVOP = 268,
     ADDOP = 269,
     MINOP = 270,
     TCEQ = 271,
     TCNE = 272,
     TCLT = 273,
     TCLE = 274,
     TCGT = 275,
     TCGE = 276,
     LPAREN = 277,
     RPAREN = 278,
     LBRACK = 279,
     RBRACK = 280,
     LBRACE = 281,
     RBRACE = 282,
     COMMA = 283,
     SEMI = 284
   };
#endif
/* Tokens.  */
#define ID 258
#define NUM 259
#define INT 260
#define VOID 261
#define RETORNO 262
#define SI 263
#define SINO 264
#define MIENTRAS 265
#define ASSIGN 266
#define MULOP 267
#define DIVOP 268
#define ADDOP 269
#define MINOP 270
#define TCEQ 271
#define TCNE 272
#define TCLT 273
#define TCLE 274
#define TCGT 275
#define TCGE 276
#define LPAREN 277
#define RPAREN 278
#define LBRACK 279
#define RBRACK 280
#define LBRACE 281
#define RBRACE 282
#define COMMA 283
#define SEMI 284




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 11 "parser.y"
{
    Nodo *nodo;
    Bloque *bloque;
    Expresion *expr;
    Sentencia *sent;
    Identificador *ident;
    DeclaracionVariable *decl_var;
    std::vector<DeclaracionVariable*> *varvec;
    std::vector<Expresion*> *exprvec;
    std::string *string;
    int token;
	long long numero;
}
/* Line 1529 of yacc.c.  */
#line 121 "parser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;
