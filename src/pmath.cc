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

#include "pmath.h"

#include <algorithm>

std::vector<double>* plotter::pmath::range(double a, double b, int n)
{
	if(a>b)
	{
		std::swap(a,b);
	}
	std::vector<double>* ans = new std::vector<double>(n);
	std::vector<double>::iterator f_a = ans->begin();
	double x = a;
        double step=(b-a)/n;
        for(;
	    f_a!=ans->end();
	    ++f_a, x+=step)
	{
		*f_a = x;
	}
	return ans;
}
std::vector<double>* plotter::pmath::map(const function* const f, const std::vector<double>* const domain)
{
	std::vector<double>* ans = new std::vector<double>(domain->size());
	std::vector<double>::const_iterator a = domain->begin();
	std::vector<double>::iterator f_a = ans->begin();
	
	for(;f_a!=ans->end();++a,++f_a)
	{
		*f_a = (*f)(*a);
	}
	return ans;
}
