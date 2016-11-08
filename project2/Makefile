test: ann.o main.o
	g++ -Wall ann.o main.o -o test

main.o: main.cpp 
	g++ -c -g -Wall main.cpp

ann.o: ann.cpp
	g++ -c -g -Wall ann.cpp
clean:
	rm *.o test
