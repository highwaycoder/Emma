#ifndef OPCODES_H
#define OPCODES_H

// some sample opcodes
enum OPCODES {
  OPCODE_NOP  = 0x0000,
  OPCODE_HLT  = 0x0001,
  // === jumps ===
  OPCODE_JMP  = 0x1000,
  // === movs ===
  OPCODE_MOV  = 0x2000,
  // === outs ===
  OPCODE_OUT  = 0x3000,
  // === inc/dec ===
  OPCODE_INC  = 0x4000,
  // === stack operations ===
  OPCODE_PUSH = 0x5000,
  OPCODE_POP  = 0x5800,
  // === arithmetic add ===
  OPCODE_ADD  = 0x6000,
  OPCODE_ADC  = 0x6001,
  // === bitwise operators (immediate versions) ==
  OPCODE_ANDI = 0x8000,
  OPCODE_ORI  = 0x8001,
  OPCODE_NORI = 0x8002,
  OPCODE_NOTI = 0x8003,
  OPCODE_XORI = 0x8004,
  OPCODe_INVI = 0x8005,
  // === interrupts, etc. ===
  OPCODE_INT  = 0xF000 // programmable? interrupts
};

// some sample outputs
enum OUTPUTS {
  OUT_CONSOLE = 0xFFFF // debugging console output
};

// some sample operands
enum OPERANDS {
  ACC = 0x00,
  REG_B = 0x01,
  REG_C = 0x02
  
};

// a helpful macro
#define OPCODE_CASE(op,func) case op:\
                              cpu = func(cpu); \
                              if(cpu->flag_reg & FLAG_ERROR) return cpu;\
                              break;

#endif
