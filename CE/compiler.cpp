#include <iostream>
#include <fstream>
#include <cstdlib>
#include "node.h"
extern Bloque* bloquePrograma;
extern int yyparse();

int main() {
    yyparse();
	std::cout << "Parsing Terminado!" << std::endl;

	std::ofstream CFile ("cfile.cpp");
	CFile << "#include <iostream>" <<std::endl;
	CFile << bloquePrograma->generarCodigo() << std::endl;
	CFile.close();

	std::string compile = "g++ cfile.cpp";
	const char *command = compile.c_str();
	system(command);

    return 0;
}
