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

#ifndef PLOTTER_MODEL_COLUMNS_H
#define PLOTTER_MODEL_COLUMNS_H

#include <gtkmm/treemodel.h>
#include "function.h"

namespace plotter 
{
    class model_columns: public Gtk::TreeModel::ColumnRecord /* NOTE only used to get the columntype */
    {
    public:
        Gtk::TreeModelColumn<gint> show; //HACK should be gboolean
        Gtk::TreeModelColumn<Glib::ustring> function; //HACK
        model_columns();
    };
}

#endif /* PLOTTER_MODEL_COLUMNS_H */
