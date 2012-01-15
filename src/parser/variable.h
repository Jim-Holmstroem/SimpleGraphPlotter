#ifndef PARSER_VARIABLE_H
#define PARSER_VARIABLE_H

#include "iexpression.h"

namespace parser {
    
    class variable : public iexpression {
    public:
        explicit variable()
        {
        };
        virtual double operator()(double x) const;
        virtual ~variable()
        {
        };
    private:
        
    };
}

#endif
