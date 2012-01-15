#include "parser.h"

#include <iostream>
#include <algorithm>
#include <cmath>
#include <sstream>

#include "unary_operation.h"
#include "binary_operation.h"

parser::parser::parser() {
    
    _functions = function_container();

        _functions["cos"] = &cos;
        _functions["sin"] = &sin;
        _functions["tan"] = &tan;
        _functions["acos"]= &acos;
        _functions["asin"]= &asin;
        _functions["atan"]= &atan;
        
        _functions["cosh"] = &cosh;
        _functions["sinh"] = &sinh;
        _functions["tanh"] = &tanh;

        _functions["exp"] = &exp;
        _functions["log"] = &log;
        _functions["log10"] = &log10;

        _functions["sqrt"] = &sqrt;
        
        _functions["ceil"] = &ceil;
        _functions["abs"] = &fabs;
        _functions["floor"] = &floor;

    _unary_ops = unary_container();
        _unary_ops[5] = unary_level();
            _unary_ops[5]['+'] = &operators::unit;
            _unary_ops[5]['-'] = &operators::neg;
    
    _binary_ops= binary_container();
        _binary_ops[0] = binary_level();
            _binary_ops[0]['>'] = &operators::gt;
            _binary_ops[0]['<'] = &operators::lt;
        _binary_ops[1] = binary_level();
            _binary_ops[1]['+'] = &operators::add;
            _binary_ops[1]['-'] = &operators::sub;
        _binary_ops[2] = binary_level();
            _binary_ops[2]['%'] = &fmod;
        _binary_ops[3] = binary_level();
            _binary_ops[3]['*'] = &operators::mul;
        _binary_ops[4] = binary_level();
            _binary_ops[4]['/'] = &operators::div;
        _binary_ops[5] = binary_level();
            _binary_ops[5]['^'] = &pow;

    _max_level=5; //NOTE magicnumber, should bu max(key)

};

bool
parser::parser::is_constant(char c) {
    return ( static_cast<int>(c) >=48 && static_cast<int>(c) <=57 );
};
parser::constant* 
parser::parser::read_constant() {
    std::string::iterator start = _at;
    
    while(is_constant(*_at)||(*_at=='.')) //is_constant as in "is_number"
        ++_at;

    double number;
    std::stringstream ss;
    ss.str(std::string(start,_at));
    ss>>number; //the error will be thrown from here, the count will only be valid if this error is not thrown
    
    return new constant(number);
};

bool 
parser::parser::is_unary_operator(char token,int level) {
    return _unary_ops[level].count(token);
};
parser::unary_operator 
parser::parser::read_unary_operator(int level) {
   return _unary_ops[level][*(++_at-1)]; //HACK
};

bool
parser::parser::is_binary_operator(char token,int level) {
    return _binary_ops[level].count(token);
};
parser::binary_operator
parser::parser::read_binary_operator(int level) {
    return _binary_ops[level][*(++_at-1)]; //HACK
};

bool
parser::parser::is_variable(char c) {
    return c=='x';
};
parser::variable*
parser::parser::read_variable() {
    ++_at;
    return new variable();
};

parser::iexpression*
parser::parser::read_expression(int level) {
    if((level-1)==_max_level) //BASE_CASE 
    {
        if(is_variable(*_at)) //NOTE using 'is_variable' to make it generic, 2D-plots next? 
        {
            return read_variable();
        }
        else if(is_function(*_at))
        {
            function f = read_function();
            ++_at; //'('

            iexpression* inner_expression = read_expression(-1);
            
            if(*(_at++)!=')') //')'
            {
                throw parse_exception(
                            std::string("missing ')' left:")+
                            std::string(_at,_expr.end())
                        );    
            }

            return new unary_operation(f,inner_expression);
        }
        else if(is_constant(*_at))
        {
            return read_constant();    
        }
        throw parse_exception("unknown syntax, whats left:'"+std::string(_at,_expr.end())+"'");
    }
    else
    { //term_i = [unary_i],term_(i+1),[op_(i+1),term_(i+1)] //NOTE smarter to use _ instead of -
        iexpression* left=NULL;
        if(is_unary_operator(*_at,level))
        {
            unary_operator uop = read_unary_operator(level); //POTENTIAL BUG: execution order unknown f(a(),b()), always do it one step at the time
            iexpression* inner_expression = read_expression(level+1);
            left = new unary_operation(uop,inner_expression); //TODO the word "expression" is large and the problem should be split up into multiple parsing step, not just one big one
        //BUG verfiy that -1+1 works (wich it don't for python)
        }
        else
        {     
            left = read_expression(level+1);
        } 
        
        if(is_binary_operator(*_at,level+1))
        {
            binary_operator bop = read_binary_operator(level+1);    
            iexpression* right = read_expression(level); //BUG? should this really be level?
            return new binary_operation(bop,left,right);
        }
        else
        { //nothing todo, just pass it on
            return left;
        }
    }
    throw parse_exception("something went wrong in the parsing, shouldn't be here");
};

bool
parser::parser::is_function(char c) {
    return (( static_cast<int>(c)>=97 && static_cast<int>(c)<=122 )&&c!='x')||c=='('; //NOTE no magic numbers
};
parser::function
parser::parser::read_function() {
    std::string::iterator last = std::find(_at,_expr.end(),'(');
    std::string name = std::string(_at,last);
    if(name.size()==0)
        return &operators::unit;

    if(!_functions.count(name)) //TODO write about how google sees exceptions as forbidden, I only use them sparsly
        throw parse_exception("'"+name+"' is not a known function.");
    
    _at+=(name.size());

    return _functions[name];
};

parser::iexpression* 
parser::parser::parse(const std::string expr) {
    _expr = expr;
    _at = _expr.begin();

    //preprocessing HACK,erase is for cleanup
    _expr.erase(std::remove_if(_expr.begin(),_expr.end(),&isspace),_expr.end());

    return read_expression(-1);
};
