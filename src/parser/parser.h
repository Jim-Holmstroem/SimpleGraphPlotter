#ifndef PARSER_PARSER
#define PARSER_PARSER

#include <string>
#include <vector>
#include <map>
#include <exception>

#include "iparser.h"
#include "constant.h"
#include "variable.h"

namespace parser {

    typedef double (*function)(double);
    typedef double (*unary_operator)(double);
    typedef double (*binary_operator)(double,double);

    typedef std::map<std::string,function> function_container; 
    typedef std::map<char,unary_operator> unary_level; 
    typedef std::map<char,binary_operator> binary_level;
    typedef std::map<int,unary_level> unary_container;
    typedef std::map<int,binary_level> binary_container;

    class parser {

    /* EBNF
    *  
    *  plots  = term-(-1),[';',expression-(-1)],'\n'
    *  expression-i = [unary-i],expression-(i+1),[op-(i+1),expression-i] (* -1 is the lower order expression *) (* either unary-(i+1) or op-(i+1), unary (since on the left) has higher priority  *)
    *  term-n = var | num | [function],(,term-(-1),) (* n is the number of the highest order operator *) (* function is operinal and if left out it will be the unit function *)
    * 
    * op-0 = '>' | '<'
    * op-1 = '+' | '-'
    * op-2 = '*' | '/' | '%'
    * op-3 = '^'
    * unary-3 = '+' | '-' | '*' 
    * num = ? all numbers ?
    * var = 'x'
    * function = sin | cos | tan | ? function specified in list ?
    *
    */
    protected:
        class operators {
        public:
            //all is static since it's need to be converted to typdef function
            static double unit(double x) { return x; };
            static double neg(double x) { return -x; };
        
            static double add(double x,double y) { return x+y; };
            static double sub(double x,double y) { return x-y; };
            static double mul(double x,double y) { return x*y; };
            static double div(double x,double y) { return x/y; };
            
            static double gt(double x,double y) { return x>y; };
            static double lt(double x,double y) { return x<y; };

        };

        class parse_exception : public std::exception {
        public:
            explicit parse_exception(std::string msg)
                : _msg(msg) 
            {
            };
            virtual const char* what() const throw()
            {
                return ("ParseException: "+_msg).c_str();
            };
            virtual ~parse_exception() throw() 
            {
            };
        protected:
            std::string _msg;
        };

    public:
        virtual iexpression* parse(std::string expr);
        
        explicit parser();

    protected:
        std::string _expr;

        iexpression* read_expression(int level);

        //NOTE always check is_* before read_*
        inline bool is_unary_operator(char token,int level);
        unary_operator read_unary_operator(int level);
        inline bool is_binary_operator(char token,int level);
        binary_operator read_binary_operator(int level);
        inline bool is_function(char c); //start of function or paratheses
        function read_function();

        inline static bool is_constant(char c);
        constant* read_constant();
        inline static bool is_variable(char c);
        variable* read_variable();

        std::string::iterator _at; //where the parse-queue is at, (pointer+_expr, works as a queue togheter)
        function_container _functions;
        unary_container _unary_ops; //map<level,map<token,operator>>
        binary_container _binary_ops;
        int _max_level;
    };

}

#endif
