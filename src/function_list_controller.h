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

#ifndef PLOTTER_FUNCTION_LIST_CONTROLLER_H
#define PLOTTER_FUNCTION_LIST_CONTROLLER_H

#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include <gtkmm/button.h>

#include "model_columns.h"
#include "plot_drawingarea.h"

namespace plotter 
{

	class function_list_controller
	{
	public:
		function_list_controller();
		function_list_controller(
		                         Gtk::TreeView* listview,
                                         plot_drawingarea* plot,
		                         Glib::RefPtr<Gtk::ListStore> store,
		                         Glib::RefPtr<Gtk::CellRendererToggle> show_cellrenderer,
		                         Glib::RefPtr<Gtk::CellRendererText> function_cellrenderer,
		                         Gtk::Button* add_button,
		                         Gtk::Button* remove_button
		                         );
	protected:
		void on_add();
		void on_remove();
		void on_selection_changed();
		void on_cell_toggled(const Glib::ustring& location);
		void on_cell_edited(const Glib::ustring& location,const Glib::ustring& data);
			
		Gtk::TreeView* _listview;
                plot_drawingarea* _plot;
		Glib::RefPtr<Gtk::TreeSelection> _selection;
		Glib::RefPtr<Gtk::ListStore> _store;
		Glib::RefPtr<Gtk::CellRendererToggle> _show_cellrenderer;
		Glib::RefPtr<Gtk::CellRendererText> _function_cellrenderer;
		Gtk::Button* _add_button;
		Gtk::Button* _remove_button;
		model_columns _model_columns; //TODO se if this sucker is used, or if it can be removed
	};

};
#endif /* PLOTTER_FUNCTION_LIST_CONTROLLER_H */
