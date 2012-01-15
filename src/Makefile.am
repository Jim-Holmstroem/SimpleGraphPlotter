## Process this file with automake to produce Makefile.in

## Created by Anjuta


uidir = $(datadir)/plotter/ui
ui_DATA = plotter.ui


AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(PLOTTER_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = plotter

plotter_SOURCES = \
	main.cc \
	model_columns.h \
	model_columns.cc \
	function_list_controller.h \
	function_list_controller.cc \
	plot_drawingarea.h \
	plot_drawingarea.cc

plotter_LDFLAGS = 

plotter_LDADD = $(PLOTTER_LIBS)


EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(datadir)/plotter

