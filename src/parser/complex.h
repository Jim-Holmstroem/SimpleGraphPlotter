#ifndef PARSER_COMPLEX
#define PARSER_COMPLEX

#include <cmath>

namespace parser {

    struct complex
    {
        double real;
        double imag;

        explicit complex(double r,double i)
            : real(r)
            , imag(i)
        {
        };
        complex(double r) //TODO write something about automatic conversion and non-excplicit constructor in c++
            : real(r)
            , imag(0)
        {
        };

        complex operator+(complex c)
        {
            return complex(real+c.real,imag+c.imag); 
        };
        complex operator-(complex c)
        {
            return complex(real-c.real,imag-c.imag);
        };
        complex operator*(complex c)
        {
            return complex( real*c.real-imag*c.imag , real*c.imag+c.imag*c.real );
        };
        complex operator*(double c) //TODO write something about these being only shortcuts, not really needed since the non-excplicit constructur deals with it converting it to an complex as needed.
        {
            return complex(c*real,c*imag);
        };
        complex conj()
        {
            return complex(real,-imag);
        };
        double abs()
        {
            return sqrt(this->abs_square());
        };
        double abs_square()
        {
            return real*real+imag*imag;
        };
        complex operator/(double d) 
        {
            return complex(real/d,imag/d);
        };
        complex operator/(complex c)
        {
            return ((*this)*c.conj())/c.abs_square();
        };

    //TODO should this be supported, why?    complex double() 

    };

};
#endif
