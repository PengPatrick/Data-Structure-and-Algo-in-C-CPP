CFLAGS=-std=gnu99 -pedantic -Wall -Werror
testPower: power.o test-power.o
	gcc -o testPower power.o test-power.o

power.o: power.c
	gcc $(CFLAGS) -c power.c

test-power.o: test-power.c
	gcc $(CFLAGS) -c test-power.c

.PHONY: clean
clean:
	rm -f testPower *.o *.c~
