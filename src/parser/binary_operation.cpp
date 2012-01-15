#include "binary_operation.h"
double
parser::binary_operation::operator()(double x) const {
    return (*_op)( (*_left)(x), (*_right)(x));    
};
