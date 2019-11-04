%{
	#include <stdio.h>
	#include "node.h"
	
	int yylex(void);
	Bloque *bloquePrograma = nullptr;

	void yyerror(const char *s) { printf("ERROR: %sn", s); }
%}

%union {
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

%token <string> ID
%token <numero> NUM
%token <token> INT VOID INPUT OUTPUT
%token <token> RETORNO SI SINO MIENTRAS
%token <token> ASSIGN MULOP DIVOP ADDOP MINOP
%token <token> TCEQ TCNE TCLT TCLE TCGT TCGE
%token <token> LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE COMMA SEMI

%type <ident> ident var
%type <expr> expresion expresion_simple expresion_aditiva term factor call
%type <varvec> params lista_params
%type <exprvec> lista_arg
%type <decl_var> param
%type <bloque> programa lista_declaracion sent_compuesta declaracion_local lista_sentencias
%type <sent> declaracion var_declaracion fun_declaracion sentencia sentencia_expresion sentencia_seleccion sentencia_iteracion sentencia_retorno sentencia_io
%type <token> tipo addop mulop comp io

%locations

%%

programa:
	lista_declaracion { bloquePrograma = $1; }
	;

lista_declaracion:
	declaracion { $$ = new Bloque(); $$->sentencias.push_back($1); }
	| lista_declaracion declaracion { $1->sentencias.push_back($2); }
	;

declaracion:
	var_declaracion
	| fun_declaracion
	;

var_declaracion:
	tipo ident SEMI { $$ = new DeclaracionVariable($1, $2); }
	| tipo ident LBRACK NUM RBRACK SEMI { $$ = new DeclaracionVariable($1, $2, $4); }
	;

fun_declaracion:
	tipo ident LPAREN params RPAREN LBRACE sent_compuesta RBRACE { $$ = new DeclaracionFuncion($1, $2, *$4, $7); }
	;

params:
	lista_params { $$ = $1; }
	| { $$ = new Variables(); }
	;

lista_params:
	param { $$ = new Variables(); $$->push_back($1); }
	| lista_params COMMA param { $1->push_back($3); }
	;

param:
	 tipo ident { $$ = new DeclaracionVariable($1, $2); }
	 | tipo ident LBRACK RBRACK { $$ = new DeclaracionVariable($1, $2, 1); }
	 ;

tipo:
	INT
	| VOID
	;

sent_compuesta:
	declaracion_local lista_sentencias {$$ = $1; $$->sentencias.insert($$->sentencias.end(), $2->sentencias.begin(), $2->sentencias.end()); }
	;

declaracion_local:
	{ $$ = new Bloque(); } 
	|declaracion_local var_declaracion { $1->sentencias.push_back($2); }
	;

lista_sentencias:
	{ $$ = new Bloque(); }
	| lista_sentencias sentencia { $1->sentencias.push_back($2); } 
	;

sentencia:
	sentencia_expresion
	| sentencia_seleccion
	| sentencia_iteracion
	| sentencia_retorno
	| sentencia_io
	;

sentencia_expresion:
	expresion SEMI { $$ = new SentenciaExpresion($1); }
	;

sentencia_seleccion:
	SI LPAREN expresion RPAREN LBRACE sent_compuesta RBRACE { $$ = new SentenciaSi($3, $6); }
	| SI LPAREN expresion RPAREN LBRACE sent_compuesta RBRACE SINO LBRACE sent_compuesta RBRACE { $$ = new SentenciaSi($3, $6, $10); }
	;

sentencia_iteracion:
	MIENTRAS LPAREN expresion RPAREN LBRACE sent_compuesta RBRACE { $$ = new SentenciaMientras($3, $6); }
	;

sentencia_retorno:
	RETORNO SEMI { $$ = new SentenciaRetorno(); }
	| RETORNO expresion SEMI { $$ = new SentenciaRetorno($2); }
	;

sentencia_io:
	io LPAREN expresion RPAREN SEMI { $$ = new SentenciaIO($1, $3); }
	;

io:
  INPUT
  | OUTPUT;

expresion:
	var ASSIGN expresion { $$ = new Asignacion($1, $3); }
	| expresion_simple
	;

var:
   ident
   | ident LBRACK expresion RBRACK { $$ = $1; $$->posicion = $3; }
   ;

ident:
	ID { $$ = new Identificador(*$1); }
	| ID LBRACK expresion RBRACK { $$ = new Identificador(*$1, $3); }
	;

expresion_simple:
	expresion_aditiva comp expresion_aditiva { $$ = new OperadorBinario($1, $2, $3); }
	| expresion_aditiva
	;

comp:
	TCEQ
	|TCNE
	|TCLT
	|TCLE
	|TCGT
	|TCGE
	;

expresion_aditiva:
	term
	| expresion_aditiva addop term { $$ = new OperadorBinario($1, $2, $3); }
	;

addop:
	 ADDOP
	 | MINOP
	 ;

term:
	factor
	| term mulop factor { $$ = new OperadorBinario($1, $2, $3); }
	;

mulop:
	 MULOP
	 | DIVOP
	 ;

factor: 
	LPAREN expresion RPAREN { $$ = $2 }
	| ident { $$ = $1; }
	| call
	| NUM { $$ = new Entero($1); }
	;

call:
	ident LPAREN lista_arg RPAREN { $$ = new LlamadaMetodo($1, *$3); } 
	| ident LPAREN RPAREN { $$ = new LlamadaMetodo($1); } 
	;

lista_arg:
	expresion { $$ = new Expresiones(); $$->push_back($1); }
	| lista_arg COMMA expresion { $1->push_back($3); }
	;

%%
