#ifndef PARSER_VARIABLE
#define PARSER_VARIABLE

#include "iexpression.h"

namespace parser {
    
    class variable : public iexpression {
    public:
        explicit variable()
        {
        };
        virtual double eval(double x) const;
        virtual ~variable()
        {
        };
    private:
        
    };
}

#endif
