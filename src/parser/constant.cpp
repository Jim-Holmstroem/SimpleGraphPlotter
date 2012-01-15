#include "constant.h"
double 
parser::constant::operator()(double x) const {
    return this->_c;
}

