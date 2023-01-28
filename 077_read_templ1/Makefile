CPPFLAGS= -std=gnu++98 -pedantic -Werror -Wall
code: code.o
	g++ -o code code.o

code.o: code.cpp
	g++ $(CPPFLAGS) -c code.cpp

clean:
	rm -f *~ code *.o
