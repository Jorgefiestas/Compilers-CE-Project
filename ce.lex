%{
#include <stdlib.h>
void yyerror(char *);
#include "y.tab.h"

%}

%option yylineno

%%

"entero" {
	return INT;
}

"sin_tipo" {
	return VOID;
}

"si" {
	return SI;
	}

"sino" {
	return SINO;
	}

"mientras" {
	return MIENTRAS;
	}

"retorno" {
	return RETORNO;
	}

"+"|"-" {
	return ADDOP;
	}

"*"|"/" {
	return MULOP;
	}

">"|"<"|">="|"<="|"=="|"!="  {
	return COMP;
	}

[0-9]+ {
	yylval = atoi(yytext);
	return NUM;
	}

[a-zA-Z]+ {
	return ID;
	}

"/*"[^*/]*"*/" ;

"(" { return LPAREN; }
")" { return RPAREN; }
"]" { return LBRACK; }
"[" { return RBRACK; }
"{" { return LBRACE; }
"}" { return RBRACE; }
";" { return SEMI; }
"," { return COMMA; }
"=" { return ASSIGN; }

"\n" ;

[ \t] ; /* skip whitespace */

. yyerror("invalid character"); // demas errores

%%

int yywrap(void) {
	return 1;
}
