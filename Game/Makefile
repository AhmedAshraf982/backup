
output: main.o Person.o Manager.o Gamer.o
	g++ main.o Person.o Manager.o Gamer.o -o output

main.o: main.cpp
	g++ -c main.cpp

Person.o: Person.cpp Person.h
	g++ -c Person.cpp

Manager.o: Manager.cpp Manager.h
	g++ -c Manager.cpp

clean:
	rm *.o output
