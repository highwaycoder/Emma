CC=gcc
CFLAGS=
LDFLAGS=

emma: main.c stack.o emma.o heap.o include/config.h include/emma.h include/stack.h include/heap.h
	$(CC) $(CFLAGS) -o emma main.c emma.o stack.o heap.o $(LDFLAGS)
  
stack.o: stack.c include/stack.h
	$(CC) -o stack.o -c stack.c $(CFLAGS)

heap.o: heap.c include/heap.h
	$(CC) -o heap.o -c heap.c $(CFLAGS)

emma.o: emma.c include/emma.h
	$(CC) -o emma.o -c emma.c $(CFLAGS)

debug:
	$(MAKE) CFLAGS="-g -DEMMA_DEBUG"

clean:
	rm -f emma stack.o emma.o heap.o
