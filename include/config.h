#ifndef CONFIG_H
#define CONFIG_H
#include <stdint.h>

typedef uint16_t ramword_t;

// this defines the maximum amount of ram we can address 
// by working out how much ramaddr_t can address
// it's actually arbitrary now, and we're using uint16_t
// to represent "ramaddr_t"
#define MAX_RAM 1024

#define STACKSIZE 256 // we'll store 256 words on the stack, to leave the rest for the heap

// this is used to determine the total size of the heap
#define HEAPSIZE (MAX_RAM-STACKSIZE)

#define MAXSIZE_FILE 1024 // actually this is fairly arbitrary


#endif
