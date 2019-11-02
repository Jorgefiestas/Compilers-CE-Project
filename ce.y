%{
	#include <stdio.h>
	int yylex(void);
	void yyerror(char *);
%}

%token NUM ID
%token INT VOID
%token ASSIGN MULOP ADDOP
%token SI SINO
%token MIENTRAS
%token COMP
%token RETORNO
%token LPAREN RPAREN
%token LBRACK RBRACK
%token LBRACE RBRACE
%token COMMA SEMI

%locations

%%

programa:
	lista_declaracion
	;

lista_declaracion:
	declaracion lista_declaracion
	| declaracion 
	;

declaracion:
	var_declaracion
	| fun_declaracion
	;

var_declaracion:
	tipo ID
	| tipo ID LBRACK NUM RBRACK
	;

fun_declaracion:
	tipo ID LPAREN params RPAREN sent_compuesta 
	;

params:
	lista_params
	|
	;

lista_params:
	lista_params COMMA param
	| param
	;

param:
	 tipo ID
	 | tipo ID LBRACK RBRACK
	 ;

tipo:
	INT
	| VOID
	;

sent_compuesta:
	LBRACE declaracion_local lista_sentencias RBRACE
	;

declaracion_local:
	declaracion_local var_declaracion
	| 
	;

lista_sentencias:
	lista_sentencias sentencia
	|
	;

sentencia:
	sentencia_compuesta
	| sentencia_seleccion
	| sentencia_iteracion
	| sentencia_retorno
	;

sentencia_compuesta:
	expresion SEMI
	| SEMI
	;

sentencia_seleccion:
	SI LPAREN expresion RPAREN LBRACE sentencia RBRACE
	| SI LPAREN expresion RPAREN LBRACE sentencia RBRACE SINO LBRACE sentencia RBRACE
	;

sentencia_iteracion:
	MIENTRAS LPAREN expresion RPAREN LBRACE sentencia RBRACE
	;

sentencia_retorno:
	RETORNO SEMI
	| RETORNO expresion SEMI
	;

expresion:
	var ASSIGN expresion
	| expresion_simple
	;

var:
	ID
	| ID LBRACK expresion RBRACK
	;

expresion_simple:
	expresion_aditiva COMP expresion_aditiva
	| expresion_aditiva
	;

expresion_aditiva:
	term ADDOP expresion_aditiva
	| term
	;

term:
	term MULOP factor
	| factor
	;

factor: 
	LPAREN expresion RPAREN
	| var
	| call
	| NUM
	;

call:
	ID LPAREN args RPAREN
	;

args:
	lista_arg
	|
	;

lista_arg:
	expresion COMMA lista_arg
	| expresion
	;

%%

extern int yylineno, yychar;
void yyerror(char *s) {
	fprintf(stderr, "%s: %d, %d\n", s, yychar, yylineno);
}

int main(void) {
	yyparse();
	return 0;
}

