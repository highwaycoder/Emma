#ifndef EMU8086_H
#define EMU8086_H
#include "heap.h"
#include "stack.h"

typedef enum ERRORS {
  ENONE           = 0x00,
  EINVALID_HEAP   = 0x01,
  EPCOVERFLOW     = 0x02,
  EBADJMP         = 0x03,
  EDEBUGMODE      = 0x04, // a purposeful error to create a coredump programmatically
  EBADOPCODE      = 0x05,
  ESTACKOVERFLOW  = 0x06,
  ESTACKUNDERFLOW = 0x07,
}err_t;

typedef enum FLAGS {
  FLAG_NONE  = 0,
  FLAG_CARRY = (1<<0),
  FLAG_SIGN  = (1<<1),
  FLAG_ERROR = (1<<15)
}flag_t;

typedef struct CPU {
	uint16_t acc; // accumulator
	ramaddr_t* reg_b; // register b
	ramaddr_t* reg_c; // register c
	flag_t flag_reg; // 0:zero, 1:carry, 2: sign 15:error
  err_t errno;
	ramaddr_t* pc; // program counter (points to a heap address)
  stack_t* stack;
} cpu_t;

void core_dump(cpu_t* cpu);
cpu_t* emu_run(cpu_t* cpu);
cpu_t* emu_mov(cpu_t* cpu);
cpu_t* emu_jmp(cpu_t* cpu);
cpu_t* emu_int(cpu_t* cpu);
cpu_t* emu_out(cpu_t* cpu);
cpu_t* emu_inc(cpu_t* cpu);
cpu_t* emu_push(cpu_t* cpu);
cpu_t* emu_pop(cpu_t* cpu);
cpu_t* emu_add(cpu_t* cpu);
cpu_t* emu_adc(cpu_t* cpu);
cpu_t* emu_andi(cpu_t* cpu);
cpu_t* emu_ori(cpu_t* cpu);
cpu_t* emu_nori(cpu_t* cpu);
cpu_t* emu_noti(cpu_t* cpu);
cpu_t* emu_xori(cpu_t* cpu);

// macro for incrementing the program counter once
#define CPU_INC_PC cpu->pc = (ramaddr_t*)cpu->pc->next;\
                                    if(cpu->pc == NULL)\
                         { cpu->flag_reg |= FLAG_ERROR;\
                              cpu->errno = EPCOVERFLOW;}

#endif
