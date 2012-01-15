#include "unary_operation.h"
double
parser::unary_operation::eval(double x) const {
    return (*_op)( _left->eval(x) );  
};
