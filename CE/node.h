#include <iostream>
#include <string>
#include <vector>

class Expresion;
class DeclaracionVariable;
class Sentencia;

typedef std::vector<Sentencia*> Sentencias;
typedef std::vector<Expresion*> Expresiones;
typedef std::vector<DeclaracionVariable*> Variables;

class Nodo {
	public:
};

class Expresion : public Nodo {
};

class Sentencia : public Nodo {
};

class Entero : public Expresion {
	public:
		long long valor;
		Entero(long long valor) :
			valor(valor) { }
};

class Identificador : public Expresion {
	public:
		std::string nombre;
		Expresion* posicion;
		Identificador(std::string nombre) : 
			nombre(nombre) { }
		Identificador(std::string nombre, Expresion *posicion) : 
			nombre(nombre), posicion(posicion) { }
};

class OperadorBinario : public Expresion {
	public:
		int operacion;
		Expresion *izquierda;
		Expresion *derecha;
		OperadorBinario(Expresion *izquierda, int operacion, Expresion *derecha) :
			izquierda(izquierda), operacion(operacion), derecha(derecha) { }
};

class LlamadaMetodo : public Expresion {
	public :
		Identificador *id;
		Expresiones argumentos;
		LlamadaMetodo(Identificador *id, Expresiones argumentos):
			id(id), argumentos(argumentos) { }
};

class Asignacion : public Expresion {
	public:
		Identificador *izquierda;
		Expresion *derecha;
		Asignacion(Identificador *izquierda, Expresion *derecha) :
			izquierda(izquierda), derecha(derecha) { }
};

class Bloque : public Expresion {
	public:
		Sentencias sentencias;
		Bloque() { }
};

class DeclaracionVariable : public Sentencia {
	public:
		int tipo;
		Identificador *id;
		bool puntero;
		unsigned long long tamano;
		DeclaracionVariable(int tipo, Identificador *id) :
			tipo(tipo), id(id) { }
		DeclaracionVariable(int tipo, Identificador *id, unsigned long long tamano) :
			tipo(tipo), id(id), puntero(true), tamano(tamano) { }
};

class DeclaracionFuncion : public Sentencia {
	public:
		const int tipo;
		const Identificador *id;
		Variables argumentos;
		Bloque *bloque;
		DeclaracionFuncion(const int tipo, Identificador *id, Variables argumentos, Bloque *bloque) :
			tipo(tipo), id(id), argumentos(argumentos), bloque(bloque) { }
};

class SentenciaSi : public Sentencia {
	public:
		Expresion *expEval;
		Bloque *expSi;
		Bloque *expSino;
		SentenciaSi(Expresion *expEval, Bloque *expSi) :
			expEval(expEval), expSi(expSi) { }
		SentenciaSi(Expresion *expEval, Bloque *expSi, Bloque *expSino) :
			expEval(expEval), expSi(expSi), expSino(expSino) { }
};

class SentenciaMientras : public Sentencia {
	public:
		Expresion *expEval;
		Bloque *expHacer;
		SentenciaMientras(Expresion *expEval, Bloque *expHacer) :
			expEval(expEval), expHacer(expHacer) { }
};

class SentenciaRetorno : public Sentencia {
	public:
		Expresion *expRet;
		SentenciaRetorno() { }
		SentenciaRetorno(Expresion *expRet) :
			expRet(expRet) { }
};

class SentenciaExpresion : public Sentencia {
	public:
		Expresion *expr;
		SentenciaExpresion(Expresion *expr) :
			expr(expr) { }
};
