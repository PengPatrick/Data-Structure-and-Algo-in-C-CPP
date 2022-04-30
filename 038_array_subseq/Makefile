CFLAGS=-std=gnu99 -Werror -Wall -pedantic

test-subseq: test-subseq.o maxSeq.o
	gcc -o test-subseq test-subseq.o maxSeq.o
test-subseq.o: test-subseq.c
	gcc $(CFLAGS) -c test-subseq.c
maxSeq.o: maxSeq.c
	gcc $(CFLAGS) -c maxSeq.c

.PHONY: clean
clean:
	rm -f *~ test-subseq *.o
