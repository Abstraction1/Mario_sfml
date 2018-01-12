CC=g++
CFLAGS=-c -Wall -std=c++11
LIBFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SOURCES=./src/
OBJECTS=./objects/
BIN=./bin/

all:
	@echo "**bla-bla-bla"
	g++ -c "$(SRC)main.cpp" -o $(OBJECTS)main.o
	g++ -o main $(OBJECTS)main.o $(LIBS)

clean:
	@echo "** Removing object files and executable..."
	rm -f main \
	rm $(OBJECTS)*.o
install:
	@echo "** Install int .../mario/bin/"
	cp main $(BIN)mario 
