%{
#include <stdlib.h>
#include "node.h"
#include "parser.hpp"
#define TOKEN(t) (yylval.token = t)

void yyerror(char *);

%}

%option yylineno

%%

"/*"[^*/]*"*/" ;
"//".* ;

"entero" {
	return TOKEN(INT);
}

"sin_tipo" {
	return TOKEN(VOID);
}

"si" {
	return TOKEN(SI);
	}

"sino" {
	return TOKEN(SINO);
	}

"mientras" {
	return TOKEN(MIENTRAS);
	}

"retorno" {
	return TOKEN(RETORNO);
	}

[0-9]+ {
	yylval.numero = atol(yytext);
	return NUM;
	}

[a-zA-Z]+ {
	yylval.string = new std::string(yytext, yyleng);
	return ID;
	}

"==" { return TOKEN(TCEQ); }
"!=" { return TOKEN(TCNE); }
"<"  { return TOKEN(TCLT); }
"<=" { return TOKEN(TCLE); }
">"  { return TOKEN(TCGT); }
">=" { return TOKEN(TCGE); }


"+" { return TOKEN(ADDOP); }
"-" { return TOKEN(MINOP); }
"*" { return TOKEN(MULOP); }
"/" { return TOKEN(DIVOP); }

"(" { return TOKEN(LPAREN); }
")" { return TOKEN(RPAREN); }
"]" { return TOKEN(LBRACK); }
"[" { return TOKEN(RBRACK); }
"{" { return TOKEN(LBRACE); }
"}" { return TOKEN(RBRACE); }
";" { return TOKEN(SEMI);   }
"," { return TOKEN(COMMA);  }
"=" { return TOKEN(ASSIGN); }

"\n" ;

[ \t] ; /* skip whitespace */

. yyerror("invalid character"); // demas errores

%%

int yywrap(void) {
	return 1;
}
