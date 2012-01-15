## Process this file with automake to produce Makefile.in

## Created by Anjuta


uidir = $(datadir)/simplegraphplotter/ui
ui_DATA = simplegraphplotter.ui


AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(SIMPLEGRAPHPLOTTER_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = simplegraphplotter

simplegraphplotter_SOURCES = \
	main.cc \
	plot_drawingarea.h \
	plot_drawingarea.cc \
	model_columns.h \
	model_columns.cc \
	function_list_controller.h \
	function_list_controller.cc

simplegraphplotter_LDFLAGS = 

simplegraphplotter_LDADD = $(SIMPLEGRAPHPLOTTER_LIBS)


EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(datadir)/simplegraphplotter

