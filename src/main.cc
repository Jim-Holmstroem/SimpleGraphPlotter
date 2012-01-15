/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cc
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

#include <gtkmm.h>
#include <iostream>
#include <string>

#include "config.h"


#ifdef ENABLE_NLS
#  include <libintl.h>
#endif


#include "plot_drawingarea.h"
#include "model_columns.h"
#include "function_list_controller.h"

/* For testing propose use the local (not installed) ui file */
/* #define UI_FILE PACKAGE_DATA_DIR"/plotter/ui/plotter.ui" */
#define UI_FILE "src/plotter.ui"
#define MULTITHREADED 1

void on_toggle(const Glib::ustring& str)
{
	std::cout << "crunk:" << str << std::endl;
};

int
main (int argc, char *argv[])
{
	
    #if MULTITHREADED
	if(!g_thread_supported()) //secure glib
		g_thread_init(NULL);
	gdk_threads_init(); //secure gtk
	gdk_threads_enter(); //obtain gtk global lock
    #endif /* MULTITHREADED */
	
	Gtk::Main kit(argc, argv);
	
	//Load the Glade file and instiate its widgets:
	Glib::RefPtr<Gtk::Builder> builder;
	try
	{
		builder = Gtk::Builder::create_from_file(UI_FILE);
	}
	catch (const Glib::FileError & ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	Gtk::Window* main_win = 0;
	builder->get_widget("main_window", main_win);

	Gtk::Frame* plot_frame = 0;
	builder->get_widget("plot_frame",plot_frame);

	plotter::plot_drawingarea* pa = new plotter::plot_drawingarea();

	plot_frame->add(*pa);
	pa->show();

	Gtk::Button* add_button = 0;
	builder->get_widget("add_button",add_button);
	Gtk::Button* remove_button = 0;
	builder->get_widget("remove_button",remove_button);
	Glib::RefPtr<Gtk::ListStore> list_store = Glib::RefPtr<Gtk::ListStore>::cast_static(builder->get_object("function_store"));
	Gtk::TreeView* function_treeview = 0;
	builder->get_widget("function_treeview",function_treeview);


	Glib::RefPtr<Gtk::CellRendererToggle> show_cellrenderer = Glib::RefPtr<Gtk::CellRendererToggle>::cast_static(builder->get_object("show_cellrenderer"));
	Glib::RefPtr<Gtk::CellRendererText> function_cellrenderer = Glib::RefPtr<Gtk::CellRendererText>::cast_static(builder->get_object("function_cellrenderer"));
	
	plotter::function_list_controller* flc = new plotter::function_list_controller(function_treeview,list_store,show_cellrenderer,function_cellrenderer,add_button,remove_button);

	Gtk::TreeModel::Row row = (*list_store->append());
	row.set_value(0,true);
	row.set_value(1,std::string("testar"));
	
	if (main_win)
	{
		kit.run(*main_win);
	}
	
	#if MULTITHREADED
	gdk_threads_leave(); //release gtk's global lock
	#endif /* MULTITHREADED */

	delete pa;
	delete flc;
	
	return 0;
}
