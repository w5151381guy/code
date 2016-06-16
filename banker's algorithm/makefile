banker.out:main.o function.o
	g++ -o banker.out main.o function.o
main.o:main.cpp
	g++ -c main.cpp
function.o:banker.h function.cpp
	g++ -c function.cpp
clean:
	rm -rf main.o function.o banker.out
