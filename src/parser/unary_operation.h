#ifndef PARSER_UNARY_OPERATION
#define PARSER_UNART_OPERATION

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
        virtual double eval(double x) const;
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
