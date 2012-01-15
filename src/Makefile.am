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

bin_PROGRAMS = simplegraphplotter \
	parser

simplegraphplotter_SOURCES = \
	main.cc \
	plot_drawingarea.h \
	plot_drawingarea.cc \
	model_columns.h \
	model_columns.cc \
	function_list_controller.h \
	function_list_controller.cc \
	math.h \
	math.cc

simplegraphplotter_LDFLAGS = 

simplegraphplotter_LDADD = $(SIMPLEGRAPHPLOTTER_LIBS)

parser_SOURCES =  \
	parser/binary_operation.cpp \
	parser/binary_operation.h \
	parser/complex.cpp \
	parser/complex.h \
	parser/constant.cpp \
	parser/constant.h \
	parser/iexpression.cpp \
	parser/iexpression.h \
	parser/iparser.cpp \
	parser/iparser.h \
	parser/parser.cpp \
	parser/parser.h \
	parser/parser_test.cpp \
	parser/parser_test.h \
	parser/unary_operation.cpp \
	parser/unary_operation.h \
	parser/variable.cpp \
	parser/variable.h \
	function.h \
	function.cc


EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(datadir)/simplegraphplotter

