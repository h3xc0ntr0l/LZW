CFLAGS = -O4

lzw: lzw.o bits.o heap.o
	cc $(CFLAGS) -o lzw lzw.o bits.o heap.o
lzw.o: lzw.c lzw.h
	cc $(CFLAGS) -c lzw.c
bits.o: bits.c lzw.h
	cc $(CFLAGS) -c bits.c
heap.o: heap.c lzw.h
	cc $(CFLAGS) -c heap.c
clean:
	rm -f *.o lzw
