CPPFLAGS=-std=gnu++98 -Werror -Wall -pedantic
code: code.o
	g++ -o code code.o
code.o: code.cpp
	g++ $(CPPFLAGS) -c code.cpp

clean:
	rm code code.o *~
