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

#ifndef MATH_H
#define MATH_H

#include <vector>


#include "function.h"

namespace plotter {

class pmath
{
public:
	static std::vector<double>* range(double a,double b,int n);
	static std::vector<double>* map(const function* const f,const std::vector<double>* const domain);
protected:

};

}

#endif // MATH_H_
