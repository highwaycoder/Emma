#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "include/stack.h"
#include "include/config.h"
#include "include/emma.h"

int main(int argc, char **argv)
{
	int i=0;
  int first_byte=0,second_byte=0;
  FILE* infile = NULL;
	ramword_t *inputbuffer = NULL;
  stack_t* stack = NULL;
  ramaddr_t* heap = NULL;
  cpu_t* cpu = NULL;
	switch(argc)
	{
		case 0:
			printf("Unsuitable environment (argc==0)\n");
			return -1;
		case 1:
			printf("Usage: emma input\n");
			return -1;
		case 2:
			if((infile = fopen(argv[1],"r")) == NULL)
			{
				printf("[error] could not open input file, check permissions.\n");
				return -1;
			}
			break;
		default:
			printf("Usage: emma input\n");
			return -1;
	}
  // initialize the CPU
  cpu = malloc(sizeof(cpu_t));
  if(cpu == NULL) return -1; // error
  memset(cpu,0,sizeof(cpu_t));
  if((inputbuffer = malloc(MAXSIZE_FILE))==NULL) return -1;
  stack = st_create(STACKSIZE);
  #ifdef EMMA_DEBUG
  fprintf(stderr,"HEAPSIZE: %d\n",HEAPSIZE);
  #endif
  heap = heap_init(HEAPSIZE);
  
  
  // read the file into memory (more complex than it first seemed)
  while(((first_byte = getc(infile)) != EOF)&&((second_byte = getc(infile)) != EOF)) {
    inputbuffer[i] = (first_byte<<8) | second_byte;
    i++;
  }
  
  #ifdef EMMA_DEBUG
  int j=0;
  printf("Loaded program: ");
  while(j<i)
  {
    printf("%.4X ",inputbuffer[j]);
    j++;
  }
  putchar('\n');
  #endif
  
  // can't continue if the input size was bigger than RAM will allow
  if(HEAPSIZE < i) 
  {
    #ifdef EMMA_DEBUG
    printf("Error: input file %s too big for processor\n",argv[1]);
    #endif
    free(inputbuffer);
    st_free(stack);
    heap_free(heap);
    free(cpu);
    fclose(infile);
    return -1;
  }
  // move the input buffer onto the heap at offset 0000h
  if(!heap_load(heap,inputbuffer,i))
  {
    #ifdef EMMA_DEBUG
    printf("Error: heap loading failed\n");
    #endif
    free(inputbuffer);
    st_free(stack);
    heap_free(heap);
    free(cpu);
    fclose(infile);
    return -1;
  }
  
  // the input buffer is no longer necessary, so we should free it
  free(inputbuffer);
  
  // set up the cpu with the stack and the heap
  cpu->stack = stack;
  cpu->pc = heap;
  
  // set the program running, return the state of the CPU at exit
  cpu = emu_run(cpu);
  
  #ifdef EMMA_DEBUG
  if((cpu->flag_reg & FLAG_ERROR)!=0) // this if was previously backwards
  {
    printf("Program halted with error: %.2X\n",cpu->errno);
    core_dump(cpu);
  }
  #endif
  
  // shutdown safely (free any used memory)
  st_free(stack);
  heap_free(heap);
  free(cpu);
  fclose(infile);
	return 0;
}
