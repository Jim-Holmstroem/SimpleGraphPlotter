/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * SimpleGraphPlotter
 * Copyright (C) Jim Holmström 2012 <jim.holmstroem@gmail.com>
 * 
SimpleGraphPlotter is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * SimpleGraphPlotter is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PARSER_FUNCTION_H
#define PARSER_FUNCTION_H

#include <string>

#include "parser/iexpression.h"

namespace plotter {

class function
{
public:
	function(); //NOTE only needed by liststore
        function(const std::string expression); 
        //NOTE non-explicit so one can write function f = "sin(x+2)" 
        //and it will get parsed and created properly
	~function();
        double operator()(double x) const {return (*_expression)(x);};
	operator bool() const{return _valid;};
        const std::string to_string() const{return _data;};
protected:
	std::string _data;
	bool _valid;
	parser::iexpression* _expression;
};

}
#endif // PARSER_FUNCTION_H
