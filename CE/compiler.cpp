#include <iostream>
#include "node.h"
extern Bloque* bloquePrograma;
extern int yyparse();

int main() {
    yyparse();
    std::cout << bloquePrograma << std::endl;
    return 0;
}
