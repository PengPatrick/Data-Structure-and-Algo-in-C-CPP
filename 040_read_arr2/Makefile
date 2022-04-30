CFLAGS=-std=gnu99 -Wall -Werror -pedantic -Wsign-compare -Wwrite-strings
test: test.o
	gcc -o test test.o
test.o: test.c
	gcc -c $(CFLAGS) test.c
.PHONY: clean
clean:
	rm -f *~ *.o
