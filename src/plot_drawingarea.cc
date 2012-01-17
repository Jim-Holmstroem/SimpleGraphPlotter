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

#include "model_columns.h"
#include "pmath.h"

plotter::plot_drawingarea::plot_drawingarea(Glib::RefPtr<Gtk::ListStore> store)
: _store(store)
{
    set_size_request (1000,1000);
    
    #ifndef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
    signal_draw().connect(sigc::mem_fun(*this, &plot_area::on_draw),false);
    #endif /* GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED */
}

plotter::plot_drawingarea::~plot_drawingarea()
{
}

bool 
plotter::plot_drawingarea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    const Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height= allocation.get_height();

    cr->scale(width/2,height/2);
    cr->translate(1,1);
    cr->set_line_width(0.001);

    const Cairo::Matrix upsidedown = Cairo::Matrix(1,0,0,-1,0,0);
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


    //TODO should do lazy-parsing, that is parsing only when it's needed, perhaps use TreeModel::row_changed(const Path& path,const iterator& iter)
    
    const Gtk::TreeModel::Children rows = _store->children();
    std::vector<function> functions;
    Gtk::TreeModel::const_iterator it;
    model_columns mc;
    for(it=rows.begin();it!=rows.end();++it)
    {
        Gtk::TreeModel::Row row=*it;
        if(row[mc.show])
        {
            Glib::ustring expression = row[mc.function]; //NOTE needed to remove the proxy
            functions.push_back(plotter::function(std::string(expression.c_str())));
        }
    }

    std::vector<function>::const_iterator f = functions.begin();

    const double a=-1;//box-x
    const double b=1;
    const double c=-1;//box-y

    const int n=500;

    const std::vector<double>* X = pmath::range(a,b,n);
    for(;f!=functions.end();++f)
    {
        if(*f) //if valid function
        {
            std::vector<double>* f_X = pmath::map(&(*f),X);
            cr->save();
            cr->set_source_rgba(1.0,1.0,1.0,0.8);
            cr->set_line_width(0.003);

            std::vector<double>::const_iterator x = X->begin(); 
            std::vector<double>::const_iterator fx= f_X->begin();
            std::vector<double>::const_iterator x_old; 
            std::vector<double>::const_iterator fx_old;

            for(;(x+1)!=X->end();)
            {
                cr->move_to(*x,*fx);
                x_old=x++;
                fx_old=fx++;
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
