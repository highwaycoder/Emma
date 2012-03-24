#ifndef OPCODES_H
#define OPCODES_H

// some sample opcodes
enum OPCODES {
  OPCODE_NOP = 0x0000,
  OPCODE_HLT = 0x0001,
  OPCODE_JMP = 0x1000,
  OPCODE_MOV = 0x2000,
  OPCODE_OUT = 0x3000,
  OPCODE_INC = 0x4000,
  OPCODE_PUSH= 0x5000,
  OPCODE_POP = 0x5800,
  OPCODE_ADD = 0x6000,
  OPCODE_ADC = 0x6800,
  OPCODE_INT = 0xA000 // programmable? interrupts
};

// some sample outputs
enum OUTPUTS {
  OUT_CONSOLE = 0xFFFF // debugging console output
};

// some sample operands
enum OPERANDS {
  REG_A = 0x00,
  REG_B = 0x01,
  REG_C = 0x02
  
};

// a helpful macro
#define OPCODE_CASE(op,func) case op:\
                              cpu = func(cpu); \
                              if(cpu->flag_reg & FLAG_ERROR) return cpu;\
                              break;

#endif
