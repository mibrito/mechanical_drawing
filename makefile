BIN=mechanical_drawing
CFLAGS=-W -Wall
GRAPHICS=`pkg-config --cflags --libs opencv`

all: $(BIN)
$(BIN): test.o main.o 
	g++ -o $(BIN) main.o test.o $(GRAPHICS)

main.o: primitives.hpp grammar.hpp main.cpp
	g++ -o main.o -c main.cpp $(CFLAGS)

test.o: primitives.hpp test.cpp test.hpp
	g++ -o test.o -c test.cpp $(CFLAGS)

clean:
	rm -rf *.o
mrproper: clean
	rm -rf $(BIN)