
CFLAGS = -c -Wall # -pedantic
CC = g++

FILE = complex iexpression variable constant unary_operation binary_operation iparser parser parser_test
OBJ = $(FILE:=.o)
SRC = $(FILE:=.cpp)
HDR = $(FILE:=.h)

BIN = parser_test

DEP = Makefile


$(BIN) : $(OBJ) $(DEP) 
	$(CC) $(OBJ) -o $(BIN)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run:
	./$(BIN) "1+sin(1+x)+2*x+1" 1
	./$(BIN) "1+sin(1+x)+2*x+1" -1
	./$(BIN) "1+sin(1+x)+2*x+1" 0
	./$(BIN) "-1" 1
	./$(BIN) "-2.71898791237897" 0
	./$(BIN) "asin(sin(x))" 1337
	./$(BIN) "tan(tan(3)+x)" 1
	./$(BIN) "-x" -1337
	./$(BIN) "+x" 13
	./$(BIN) "3/-1" 1
	./$(BIN) "3/-x" 3
	./$(BIN) "25%(x+1)" 1
	./$(BIN) "x>2" 3
	./$(BIN) "x<2" 2
	./$(BIN) "x^2-1>1" 2
	./$(BIN) "2*x^2-x" 1
	./$(BIN) "-1+1" 0

memcheck:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./$(BIN) "sin(x+1)+1" 1

clean:
	rm -f $(OBJ) $(BIN)

