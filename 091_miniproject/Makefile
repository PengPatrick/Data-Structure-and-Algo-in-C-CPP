CPPFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3
all: path-step1 path-step2 path-step3 path-step4

path-step1: readFile.o path-step1.o pathPlanning.o
	g++ -o path-step1 readFile.o path-step1.o pathPlanning.o

path-step2: readFile.o path-step2.o pathPlanning.o
	g++ -o path-step2 readFile.o path-step2.o pathPlanning.o

path-step3: readFile.o path-step3.o pathPlanning.o
	g++ -o path-step3 readFile.o path-step3.o pathPlanning.o

path-step4: readFile.o path-step4.o pathPlanning.o
	g++ -o path-step4 readFile.o path-step4.o pathPlanning.o

readFile.o: readFile.cpp
	g++ $(CPPFLAGS) -c readFile.cpp

pathPlanning.o: pathPlanning.cpp
	g++ $(CPPFLAGS) -c pathPlanning.cpp

path-step1.o: path-step1.cpp
	g++ $(CPPFLAGS) -c path-step1.cpp

path-step2.o: path-step2.cpp
	g++ $(CPPFLAGS) -c path-step2.cpp

path-step3.o: path-step3.cpp
	g++ $(CPPFLAGS) -c path-step3.cpp

path-step4.o: path-step4.cpp
	g++ $(CPPFLAGS) -c path-step4.cpp


.PHONY: clean
clean:
	rm -f *.o *~ path-step1 path-step2 path-step3 path-step4 readFile pathPlanning
