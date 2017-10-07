all: exe

exe: main.cpp functions.cpp
	g++ -std=c++11 main.cpp functions.cpp -o exe

clean:
	rm *.o exe