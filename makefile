BIN=mechanical_drawing
CFLAGS=-W -Wall -Werror -g3
GRAPHICS=`pkg-config --cflags --libs opencv`

all: $(BIN)
$(BIN): primitives.o test.o program.o gp.o main.o
	g++ -o $(BIN) main.o gp.o test.o program.o primitives.o -g3 $(GRAPHICS)

main.o: primitives.hpp program.hpp main.cpp
	g++ -o main.o -c main.cpp $(CFLAGS)

test.o: primitives.hpp test.cpp test.hpp
	g++ -o test.o -c test.cpp $(CFLAGS)

program.o: program.hpp program.cpp
	g++ -o program.o -c program.cpp $(CFLAGS)

primitives.o: primitives.cpp primitives.hpp
	g++ -o primitives.o -c primitives.cpp $(CFLAGS)

gp.o: gp.cpp gp.hpp program.hpp primitives.hpp
	g++ -o gp.o -c gp.cpp $(CFLAGS)

clean:
	rm -rf *.o
mrproper: clean
	rm -rf $(BIN)