#include "unary_operation.h"
double
parser::unary_operation::operator()(double x) const {
    return (*_op)( (*_left)(x) );  
};
