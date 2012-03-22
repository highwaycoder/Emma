CC=gcc
CFLAGS=
LDFLAGS=

emma: main.c stack.o emu8086.o heap.o include/config.h include/emu8086.h include/stack.h include/heap.h
	$(CC) $(CFLAGS) -o emma main.c emu8086.o stack.o heap.o $(LDFLAGS)
  
stack.o: stack.c include/stack.h
	$(CC) -o stack.o -c stack.c $(CFLAGS)

heap.o: heap.c include/heap.h
	$(CC) -o heap.o -c heap.c $(CFLAGS)

emu8086.o: emu8086.c include/emu8086.h
	$(CC) -o emu8086.o -c emu8086.c $(CFLAGS)

debug:
	$(MAKE) CFLAGS="-g -DEMMA_DEBUG"

clean:
	rm -f emma stack.o emu8086.o heap.o
