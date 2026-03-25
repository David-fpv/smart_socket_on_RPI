XX = g++
CXXFLAGS = -Wall -Wextra -std=c++20
LIBS = -lgpiod

SRCS = main.cpp GpioController.cpp

all: main

main: main.o GpioController.o
	$(CXX) main.o GpioController.o -o main $(LIBS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

GpioController.o: GpioController.cpp
	$(CXX) $(CXXFLAGS) -c GpioController.cpp -o GpioController.o

clean:
	rm -f *.o
