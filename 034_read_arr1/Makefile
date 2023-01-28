CfLAGS=-std=gnu99 -Wall -Werror -pedantic

test: test.o
	gcc -o test test.o

test.o: test.c
	gcc -c test.o $(CFLAGS) test.c

.PHONY: clean
clean:
	rm -f test *.o *.c~
