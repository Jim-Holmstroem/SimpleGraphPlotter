/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * plotter
 * Copyright (C) Jim Holmström 2012 <jim.holmstroem@gmail.com>
 * 
plotter is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * plotter is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "plot_drawingarea.h"

#include <iostream>

#include <glibmm/main.h>
#include <cairomm/matrix.h>

#include "pmath.h"

plotter::plot_drawingarea::plot_drawingarea()
{
	set_size_request (1000,1000);
	
	#ifndef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
	singal_draw().connect(sigc::mem_fun(*this, &plot_area::on_draw),false);
	#endif /* GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED */
}

plotter::plot_drawingarea::~plot_drawingarea()
{
}

bool 
plotter::plot_drawingarea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height= allocation.get_height();

	cr->scale(width/2,height/2);
	cr->translate(1,1);
	cr->set_line_width(0.001);

        Cairo::Matrix upsidedown = Cairo::Matrix(1,0,0,-1,0,0);
        cr->transform(upsidedown);
	cr->save();
	cr->set_source_rgba(0.0,0.0,0.0,1.0); //green
	cr->paint();
	cr->restore();
	
	cr->save();
	cr->set_source_rgba(1.0,1.0,1.0,1.0);
	cr->move_to(0.0,-1.0);
	cr->line_to(0.0,1.0);
	cr->move_to(-1.0,0.0);
	cr->line_to(1.0,0.0);
	cr->stroke();
	cr->restore();

	std::vector<function>::const_iterator f = _functions.begin();

	double a=-1;
	double b=1;
	int n=1000;

	std::vector<double>* X = pmath::range(a,b,n);
	for(;f!=_functions.end();++f)
	{
		if(*f)
		{
			std::vector<double>* f_X = pmath::map(&(*f),X);
			cr->save();
			cr->set_source_rgba(1.0,1.0,1.0,0.8);
                        cr->set_line_width(0.003);

			std::vector<double>::const_iterator x = X->begin(); 
			std::vector<double>::const_iterator fx= f_X->begin();
			for(;x!=X->end();)
			{
                                std::cout << "(" << *x << "," << *fx << ")" << std::endl;
                                cr->move_to(*x,*fx);
				++x;++fx;
				cr->line_to(*x,*fx);
			}

			cr->stroke();
			cr->restore();
		}
	}
	
	cr->stroke_preserve();
	cr->clip();

	return true; //SUCCESS
	
}
