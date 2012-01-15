#ifndef PARSER_UNARY_OPERATION_H
#define PARSER_UNART_OPERATION_H

#include "iexpression.h"

namespace parser {
    
    typedef double(*unary_op)(double);
    class unary_operation : public iexpression {
    public:
        explicit unary_operation(unary_op op, iexpression * left)
        : _op(op)
        , _left(left)
        {  
        };
        virtual double operator()(double x) const;
        virtual ~unary_operation() 
        {
            delete _left;
        };

    private:
        unary_op _op;
        iexpression * _left;
    
    };
    
}

#endif
