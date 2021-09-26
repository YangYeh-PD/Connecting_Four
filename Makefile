Connecting_Four: Connecting_Four.o Board.o
	g++ -o Connecting_Four Connecting_Four.o Board.o

Connecting_Four.o: Connecting_Four.cpp Board.h
	gcc -c Connecting_Four.cpp

Board.o: Board.cpp Board.h
	gcc -c Board.cpp

clean:
	rm Connecting_Four *.o