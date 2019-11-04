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
		virtual std::string generarCodigo() { return "Error"; };
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
	std::string generarCodigo();
};

class Identificador : public Expresion {
	public:
		std::string nombre;
		Expresion* posicion;
		Identificador(std::string nombre) : 
			nombre(nombre) { }
		Identificador(std::string nombre, Expresion *posicion) : 
			nombre(nombre), posicion(posicion) { }
	std::string generarCodigo();
};

class OperadorBinario : public Expresion {
	public:
		int operacion;
		Expresion *izquierda;
		Expresion *derecha;
		OperadorBinario(Expresion *izquierda, int operacion, Expresion *derecha) :
			izquierda(izquierda), operacion(operacion), derecha(derecha) { }
	std::string generarCodigo();
};

class LlamadaMetodo : public Expresion {
	public :
		Identificador *id;
		Expresiones argumentos;
		LlamadaMetodo(Identificador *id):
			id(id), argumentos() { }
		LlamadaMetodo(Identificador *id, Expresiones argumentos):
			id(id), argumentos(argumentos) { }
	std::string generarCodigo();
};

class Asignacion : public Expresion {
	public:
		Identificador *izquierda;
		Expresion *derecha;
		Asignacion(Identificador *izquierda, Expresion *derecha) :
			izquierda(izquierda), derecha(derecha) { }
	std::string generarCodigo();
};

class Bloque : public Expresion {
	public:
		Sentencias sentencias;
		Bloque() { }
	std::string generarCodigo();
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
	std::string generarCodigo();
};

class DeclaracionFuncion : public Sentencia {
	public:
		const int tipo;
		const Identificador *id;
		Variables argumentos;
		Bloque *bloque;
		DeclaracionFuncion(const int tipo, Identificador *id, Variables argumentos, Bloque *bloque) :
			tipo(tipo), id(id), argumentos(argumentos), bloque(bloque) { }
	std::string generarCodigo();
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
	std::string generarCodigo();
};

class SentenciaMientras : public Sentencia {
	public:
		Expresion *expEval;
		Bloque *expHacer;
		SentenciaMientras(Expresion *expEval, Bloque *expHacer) :
			expEval(expEval), expHacer(expHacer) { }
	std::string generarCodigo();
};

class SentenciaRetorno : public Sentencia {
	public:
		Expresion *expRet;
		SentenciaRetorno() { }
		SentenciaRetorno(Expresion *expRet) :
			expRet(expRet) { }
	std::string generarCodigo();
};

class SentenciaExpresion : public Sentencia {
	public:
		Expresion *expr;
		SentenciaExpresion(Expresion *expr) :
			expr(expr) { }
	std::string generarCodigo();
};

class SentenciaIO : public Sentencia {
	public:
		int op;
		Expresion *expr;
		SentenciaIO(int op, Expresion *expr) :
			op(op), expr(expr) { }
	std::string generarCodigo();
};
