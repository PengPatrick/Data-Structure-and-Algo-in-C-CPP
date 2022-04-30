CPPFLAGS=-std=gnu++11 -pedantic -Werror -Wall -ggdb3
code: code.o
	g++ -ggdb3 -o code code.o
code.o: code.cpp
	g++ $(CPPFLAGS) -c code.cpp
.PHONY: clean
clean:
	rm -f *.o *.c~ code
