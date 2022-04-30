CFLAGS=-std=gnu99 -ggdb3 -Wall -Werror -pedantic
test: test.o
	gcc -o  test test.o
test.o: test.c
	gcc -c $(CFLAGS) test.c
.PHONY: clean
clean:
	rm -f *.o *.c~ *.h~
