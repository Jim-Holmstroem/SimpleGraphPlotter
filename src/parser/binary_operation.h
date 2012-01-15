#ifndef PARSER_BINARY_OPERATION
#define PARSER_BINARY_OPERATION

#include "iexpression.h"

namespace parser {
   
    typedef double(*binary_op)(double,double);
    class binary_operation : public iexpression {
    public:
        explicit binary_operation(binary_op op,iexpression * left,iexpression * right)
        : _op(op)
        , _left(left)
        , _right(right)
        {
        };
        virtual double eval(double x) const;
        virtual ~binary_operation()
        {
            delete _left;
            delete _right;
        };

    private:
        binary_op _op;
        iexpression * _left;
        iexpression * _right;

    }; 
    
}

#endif
