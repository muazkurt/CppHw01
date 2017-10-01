all: exe

exe: main.o functions.o
	g++ -o exe functions.o main.o

main.o: 
	g++ -c main.cpp

functions.o: functions.cpp
	g++ -c functions.cpp

clean:
	rm *.o exe