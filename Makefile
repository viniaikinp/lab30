all: utils.o book.o shelf.o rack.o library.o menu.o main.o main

utils.o: utils.cpp
	g++ -std=c++11 -c -o utils.o utils.cpp

book.o: book.cpp
	g++ -std=c++11 -c -o book.o book.cpp

shelf.o: shelf.cpp
	g++ -std=c++11 -c -o shelf.o shelf.cpp

rack.o: rack.cpp
	g++ -std=c++11 -c -o rack.o rack.cpp

library.o: library.cpp
	g++ -std=c++11 -c -o library.o library.cpp

menu.o: menu.cpp
	g++ -std=c++11 -c -o menu.o menu.cpp

main.o: main.cpp
	g++ -std=c++11 -c -o main.o main.cpp

main: main.o
	g++ -std=c++11 utils.o book.o shelf.o rack.o library.o menu.o main.o -o laba

clean:
	rm *.o

