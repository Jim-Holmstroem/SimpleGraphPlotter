#include "binary_operation.h"
double
parser::binary_operation::eval(double x) const {
    return (*_op)( _left->eval(x), _right->eval(x));    
};
