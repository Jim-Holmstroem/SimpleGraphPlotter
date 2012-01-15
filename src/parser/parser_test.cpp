#include "parser_test.h"

#include <iostream>
#include <string>
#include <sstream>

#include "parser.h"
#include "iexpression.h"

int 
main(int argc,const char* argv[]) {
    parser::parser p = parser::parser();
    std::cout.precision(15);
	
    parser::iexpression* e = p.parse(argv[1]);

    std::stringstream ss;
    ss.str(argv[2]);
    double x;
    ss>>x;

    std::cout << e->eval(x) << std::endl;

    delete e;

};
