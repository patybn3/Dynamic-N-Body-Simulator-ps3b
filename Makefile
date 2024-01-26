CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
# Your .hpp files
DEPS = Universe.hpp CelestialBody.hpp
# Your compiled .o files
OBJECTS = Universe.o CelestialBody.o
# The name of your program
PROGRAM = NBody
TEST = test

.PHONY: all clean lint

all: $(PROGRAM) $(TEST) NBody.a

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(TEST): test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

NBody.a: $(OBJECTS)
	ar rcs NBody.a $(OBJECTS)

clean:
	rm *.o $(PROGRAM) $(TEST) NBody.a

lint:
	cpplint *.cpp *.hpp
