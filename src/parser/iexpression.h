#ifndef PARSER_IEXPRESSION
#define PARSER_IEXPRESSION

namespace parser {
    
    class iexpression {   
    public:
        virtual double operator()(double x) const = 0;
        virtual ~iexpression(){};
    };

}

#endif
