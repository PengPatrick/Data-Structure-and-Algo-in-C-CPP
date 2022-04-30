CFLAGS=-std=gnu99 -Werror -Wall -pedantic
all: step1 step2 step3

step1: step1.c
	-gcc -g $(CFLAGS) step1.c

step2: step2.c
	-gcc -g $(CFLAGS) step2.c

step3: step3.c
	-gcc -g $(CFLAGS) step3.c

.PHONY: clean
clean:
	-rm -f step1 *.o *.c~ *.h~
