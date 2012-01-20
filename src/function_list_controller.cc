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

#include "function_list_controller.h"

#include <iostream>
#include <vector>

#include <gtkmm/treemodel.h>
#include <gtkmm/treeselection.h>
#include <gtkmm/treerowreference.h>


plotter::function_list_controller::function_list_controller(
        Gtk::TreeView& listview /*view*/,
        plot_drawingarea& plot /*2nd view*/,
        Glib::RefPtr<Gtk::ListStore> store /*model*/,
        Glib::RefPtr<Gtk::CellRendererToggle> show_cellrenderer,
        Glib::RefPtr<Gtk::CellRendererText> function_cellrenderer,
        Gtk::Button& add_button,
        Gtk::Button& remove_button
        ) 
: _listview(listview)
, _plot(plot)
, _store(store)
, _show_cellrenderer(show_cellrenderer)
, _function_cellrenderer(function_cellrenderer)
, _add_button(add_button)
, _remove_button(remove_button)
{
	_add_button.signal_clicked().connect(
                sigc::mem_fun(
                    *this,
                    &function_list_controller::on_add
                    )
                );
	_remove_button.signal_clicked().connect(
                sigc::mem_fun(
                    *this,
                    &function_list_controller::on_remove
                    )
                );
	_selection = _listview.get_selection();
	_selection->signal_changed().connect(
                sigc::mem_fun(
                    *this,
                    &function_list_controller::on_selection_changed
                    )
                ); 
	_show_cellrenderer->signal_toggled().connect(
                sigc::mem_fun(
                    *this,
                    &function_list_controller::on_cell_toggled
                    )
                );
	_function_cellrenderer->signal_edited().connect(
                sigc::mem_fun(
                    *this,
                    &function_list_controller::on_cell_edited
                    )
                );
}

void
plotter::function_list_controller::on_add()
{
    _store->append();
}

void
plotter::function_list_controller::on_remove()
{
    std::vector<Gtk::TreeModel::Path> paths = _selection->get_selected_rows();
    std::vector<Gtk::TreeModel::RowReference> rows; 
    std::vector<Gtk::TreeModel::Path>::iterator it;
    for(it=paths.begin(); it!=paths.end(); ++it)
        rows.push_back(Gtk::TreeModel::RowReference(_store,*it));
    std::vector<Gtk::TreeModel::RowReference>::iterator jt;
    for(jt = rows.begin(); jt!=rows.end(); ++jt)
    {
        Gtk::TreeModel::iterator tree_it = _store->get_iter(jt->get_path());
        _store->erase(tree_it);
    }
    _plot.queue_draw();
}

void
plotter::function_list_controller::on_selection_changed()
{
    _remove_button.set_sensitive(_selection->count_selected_rows()>0);
}

int int_not(int a) //HACK, works like !(.) but preserves int type
{
    if(a)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void
plotter::function_list_controller::on_cell_toggled(
        const Glib::ustring& path
        )
{
    Gtk::TreeModel::iterator loc = 
        _store->get_iter(
                Gtk::TreeModel::Path(path)
                );
    loc->set_value(
            _model_columns.show, 
            int_not(
                static_cast<int>((*loc)[_model_columns.show])
                )
            ); //NOTE to get the return-type we are using model_columns
    _plot.queue_draw();
}

void
plotter::function_list_controller::on_cell_edited(
        const Glib::ustring& path,
        const Glib::ustring& data
        )
{
    Gtk::TreeModel::iterator loc = 
        _store->get_iter(
                Gtk::TreeModel::Path(path)
                );
    loc->set_value(1,std::string(data));
    if(!data.empty())
    {
        loc->set_value(0,1);
    }
    _plot.queue_draw();
}
