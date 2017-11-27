BIN=mechanical_drawing
CFLAGS=-W -Wall -Werror -g3 -O3  -std=c++11
GRAPHICS=`pkg-config --cflags --libs opencv`

# INCLUDE_DIRS += $(shell brew --prefix)/include
# LIBRARY_DIRS += $(shell brew --prefix)/lib

all: $(BIN)
$(BIN): random.o primitives.o program.o test.o gp.o main.o
	g++ $(GRAPHICS) -o $(BIN) main.o gp.o test.o program.o primitives.o random.o

main.o: gp.hpp main.cpp
	g++ $(CFLAGS) -c -o main.o main.cpp

gp.o: gp.cpp gp.hpp program.hpp primitives.hpp random.hpp
	g++ $(CFLAGS) -c -o gp.o gp.cpp

test.o: primitives.hpp test.cpp test.hpp
	g++ $(CFLAGS) -c -o test.o test.cpp

program.o: program.hpp program.cpp random.hpp
	g++ $(CFLAGS) -c -o program.o program.cpp

primitives.o: primitives.cpp primitives.hpp random.hpp
	g++ $(CFLAGS) -c -o primitives.o primitives.cpp

random.o: random.hpp random.cpp
	g++ $(CFLAGS) -c -o random.o random.cpp

clean:
	rm -rf *.o
mrproper: clean
	rm -rf $(BIN)
