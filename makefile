BIN=mechanical_drawing
CFLAGS=-W -Wall -Werror -g3 -O3
GRAPHICS=`pkg-config --cflags --libs opencv`

all: $(BIN)
$(BIN): random.o primitives.o test.o program.o gp.o main.o
	g++ -o $(BIN) main.o gp.o test.o program.o primitives.o random.o -g3 -O3 -pthread $(GRAPHICS)

main.o: gp.hpp main.cpp
	g++ -o main.o -c main.cpp $(CFLAGS)

random.o: random.hpp random.cpp
	g++ -o random.o -c random.cpp $(CFLAGS)

test.o: primitives.hpp test.cpp test.hpp
	g++ -o test.o -c test.cpp $(CFLAGS)

program.o: program.hpp program.cpp random.hpp
	g++ -o program.o -c program.cpp $(CFLAGS)

primitives.o: primitives.cpp primitives.hpp random.hpp
	g++ -o primitives.o -c primitives.cpp $(CFLAGS)

gp.o: gp.cpp gp.hpp program.hpp primitives.hpp random.hpp
	g++ -o gp.o -c gp.cpp $(CFLAGS)

clean:
	rm -rf *.o
mrproper: clean
	rm -rf $(BIN)