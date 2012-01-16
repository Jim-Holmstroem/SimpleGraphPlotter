
CPPFLAGS = -c -Wall `pkg-config --cflags gtkmm-3.0` # -pedantic
LIBS = `pkg-config --libs gtkmm-3.0`

CC = g++

FILE = main function function_list_controller model_columns plot_drawingarea pmath 
OBJ = $(FILE:=.o)
SRC = $(FILE:=.cc)
HDR = $(FILE:=.h)

BIN = simplegraphplotter

DEP = Makefile

all: $(BIN) 

$(BIN) : $(OBJ) $(DEP)
	$(CC) $(OBJ) `echo parser/*.o | tr ' ' "\n" | egrep -v parser/parser_test.o` -o $(BIN) $(LIBS)

$(OBJ): %.o: %.cc
	$(CC) $< -o $@ $(CPPFLAGS)
	
run:
	./$(BIN) 

memcheck:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./$(BIN)

clean:
	rm -f $(OBJ) $(BIN)

