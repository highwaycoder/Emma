#ifndef OPCODES_H
#define OPCODES_H

// some sample opcodes
enum OPCODES {
  OPCODE_NOP = 0x00,
  OPCODE_HLT = 0x01, // halt  execution
  OPCODE_JMP = 0x02,
  OPCODE_MOV = 0x03,
  OPCODE_OUT = 0x04, // send data to an output
  OPCODE_INT = 0x10 // programmable? interrupts
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
