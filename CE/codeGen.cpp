#include "node.h"
#include "parser.hpp"

typedef std::vector<Identificador*> Identificadores;
typedef std::vector<DeclaracionFuncion*> Funciones;

std::vector<Identificadores> variables;
std::vector<Funciones> funciones;

unsigned long long blck_idx = -1;

bool buscarFuncionLocal(DeclaracionFuncion *fun){

	for (int i = 0; i < funciones[blck_idx].size(); i++) {
		DeclaracionFuncion *funComp = funciones[blck_idx][i];
		if (fun->id->nombre != funComp->id->nombre) {
			continue;
		}
		if (fun->argumentos.size() != funComp->argumentos.size()) {
			continue;
		}

		bool sonIguales = true;
		for (int j = 0; j < fun->argumentos.size(); j++) {
			if(fun->argumentos[i]->tipo != funComp->argumentos[i]->tipo) {
				sonIguales = false;
				break;
			}
		}

		if(sonIguales) {
			return true;
		}
	}

	return false;
}

bool buscarFuncionGlobal(LlamadaMetodo *fun){

	for (int k = blck_idx; k >= 0; k--) {
		for (int i = 0; i < funciones[k].size(); i++) {
			DeclaracionFuncion *funComp = funciones[k][i];
			if (fun->id->nombre != funComp->id->nombre) {
				continue;
			}
			if (fun->argumentos.size() != funComp->argumentos.size()) {
				continue;
			}
			return true;
		}
	}

	return false;
}

bool buscarVariableLocal(std::string &var){

	for (int i = 0; i < variables[blck_idx].size(); i++) {
		if(var == variables[blck_idx][i]->nombre){
			return true;
		}
	}

	return false;
}

bool buscarVariableGlobal(Identificador *var){
	for (int k = blck_idx; k >= 0; k--) {
		for (int i = 0; i < variables[k].size(); i++) {
			if(var->nombre == variables[k][i]->nombre && !!(var->posicion) == !!(variables[k][i]->posicion)){
				return true;
			}
		}
	}

	return false;
}

std::string Entero::generarCodigo(){
	return std::to_string(valor);
}

std::string Identificador::generarCodigo(){
	if (!buscarVariableGlobal(this)) {
		std::cerr << "Este identificador no existe: " << nombre << std::endl;
	}

	std::string codigoIdentificador = nombre;

	if (posicion) {
		codigoIdentificador += "[" + posicion->generarCodigo() + "]";
	}

	return codigoIdentificador;
}

std::string OperadorBinario::generarCodigo(){
	std::string codigoOpBin;

	codigoOpBin = "(" + izquierda->generarCodigo() + ") ";

	switch (operacion) {
		case TCEQ:
			codigoOpBin += "==";
			break;
		case TCNE:
			codigoOpBin += "!=";
			break;
		case TCLT:
			codigoOpBin += "<";
			break;
		case TCLE:
			codigoOpBin += "<=";
			break;
		case TCGT:
			codigoOpBin += ">";
			break;
		case TCGE:
			codigoOpBin += ">=";
			break;
		case MULOP:
			codigoOpBin += "*";
			break;
		case DIVOP:
			codigoOpBin += "/";
			break;
		case ADDOP:
			codigoOpBin += "+";
			break;
		case MINOP:
			codigoOpBin += "-";
			break;
	}

	codigoOpBin += " (" + derecha->generarCodigo() + ")";

	return codigoOpBin;
}

std::string LlamadaMetodo::generarCodigo(){
	if (!buscarFuncionGlobal(this)) {
		std::cerr << "Llamando una funcion que no existe!" << id->nombre << std::endl;
	}

	std::string codigoArgumentos;
	for(int i = 0; i < argumentos.size(); i++){
		if(i != 0){
			codigoArgumentos += ", ";
		}
		codigoArgumentos += argumentos[i]->generarCodigo();
	}

	std::string codigoLlamada =  id->nombre + "(" + codigoArgumentos + ")";

	return codigoLlamada;
}

std::string Asignacion::generarCodigo(){
	return izquierda->generarCodigo() + " = " + derecha->generarCodigo();
}

std::string Bloque::generarCodigo(){
	std::string codigoBloque;

	variables.push_back(Identificadores());
	funciones.push_back(Funciones());
	blck_idx++;

	for (int i = 0; i < sentencias.size(); i++) {
		codigoBloque += sentencias[i]->generarCodigo();
		codigoBloque += ";\n";
	}

	variables.pop_back();
	funciones.pop_back();
	blck_idx--;

	return codigoBloque;
}

std::string DeclaracionFuncion::generarCodigo(){
	if (buscarFuncionLocal(this)) {
		std::cerr << "Redeclarando la funcion" << id->nombre << std::endl;
	}

	funciones[blck_idx].push_back(this);

	std::string codigoTipo;
	switch (tipo) {
		case INT:
			codigoTipo = "int";
			break;
		case VOID:
			codigoTipo = "void";
			break;
	}

	std::string codigoArgumentos;
	for(int i = 0; i < argumentos.size(); i++){
		if(i != 0){
			codigoArgumentos += ", ";
		}
		codigoArgumentos += argumentos[i]->generarCodigo();
	}

	std::string codigoBloque = bloque->generarCodigo();

	std::string codigoFuncion = codigoTipo + " " + id->nombre + "(" + codigoArgumentos + "){ \n" + codigoBloque + "}";

	return codigoFuncion;
}

std::string DeclaracionVariable::generarCodigo(){

	if (buscarVariableLocal(id->nombre)) {
		std::cerr << "Redeclarando la variable" << id->nombre << std::endl;
	}

	std::string codigoTipo;
	switch (tipo) {
		case INT:
			codigoTipo = "int";
			break;
		case VOID:
			codigoTipo = "void";
			break;
	}

	std::string codigoVariable = codigoTipo + " " + id->nombre;

	if(puntero){
		codigoVariable += "[";
		if(tamano){
			codigoVariable += tamano;
		}
		codigoVariable += "]";
	}

	variables[blck_idx].push_back(id);

	return codigoVariable;
}


std::string SentenciaSi::generarCodigo(){
	std::string codigoSi = "if(" + expEval->generarCodigo() + "){\n" + expSi->generarCodigo() + "}";

	if(expSino){
		codigoSi += "else{\n" + expSino->generarCodigo() + "}";
	}

	return codigoSi;
}

std::string SentenciaMientras::generarCodigo(){
	std::string codigoMientras = "while(" + expEval->generarCodigo() + "){\n" + expHacer->generarCodigo() + "}";

	return codigoMientras;
}

std::string SentenciaRetorno::generarCodigo(){
	std::string codigoRetorno = "return ";

	if (expRet) {
		codigoRetorno += expRet->generarCodigo();
	}

	return codigoRetorno;
}

std::string SentenciaExpresion::generarCodigo(){
	std::string codigoExpresion = expr->generarCodigo();

	return codigoExpresion;
}

std::string SentenciaIO::generarCodigo(){

	std::string codigoIO = expr->generarCodigo();
	switch(op){
		case INPUT:
			codigoIO = "std::cin >> " + expr->generarCodigo();
			break;
		case OUTPUT:
			codigoIO = "std::cout << " + expr->generarCodigo() + " << std::endl";
			break;
	}

	return codigoIO;
}
