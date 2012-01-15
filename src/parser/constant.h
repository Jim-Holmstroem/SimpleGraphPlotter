#ifndef PARSER_CONSTANT
#define PARSER_CONSTANT

#include "iexpression.h"

namespace parser {

    class constant : public iexpression {
    public:
        explicit constant(double c)
            : _c(c) 
        {
        };
        virtual double eval(double x) const;
        virtual ~constant() 
        {
        };    
    private:
        double _c;
        
    };

}

#endif
