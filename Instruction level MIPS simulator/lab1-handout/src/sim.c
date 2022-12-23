#include <stdio.h>
#include "shell.h"

#define SRLV 000110
#define SUB 100010
#define SLT 101010
#define MTLO 010011
#define SRAV 000111
#define SUBU 100011
#define SLTU 101011
#define MULTU 011001
#define SLL 000000
#define JR 001000
#define AND 100100
#define MULT 011000
#define DIV 011010
#define DIVU 011011
#define SRL 000010
#define JALR 001001
#define OR 100101
#define SRA 000011
#define ADD 100110
#define XOR 100110
#define MFLO 010010
#define SYSCALL 001100
#define NOR 100111
#define SLLV 000100
#define MTHI 010001
#define MFHI 010000
#define ADDU 100001

#define J 000010
#define ADDI 001000
#define XORI 001110
#define LHU 100101
#define BLTZAL 000001
#define JAL 000011
#define ADDIU 001001
#define LUI 001111
#define SB 001111
#define BGEZAL 000001
#define BEQ 000100
#define SLTI 001010
#define LB 100000
#define SH 101001
#define BNE 000101
#define SLTIU 001011
#define LH 100001
#define SW 101011
#define BLEZ 000110
#define ANDI 001100
#define LW 100011
#define BLTZ 000001
#define BGTZ 000111
#define ORI 001101
#define LBU 100100
#define BGEZ 000001



	

void process_instruction()
{
    /* execute one instruction here. You should use CURRENT_STATE and modify
     * values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
     * access memory. */
	//fetch instrcution from current PC
	uint32_t curr_ins = mem_read_32(CURRENT_STATE.PC);
	//extracting opcode	
	uint32_t opcode = curr_ins>>26;
	
	NEXT_STATE = CURRENT_STATE;
    	//updating PC
	NEXT_STATE.PC += 4;
	
	if(opcode == 0) {
		//R-Type instruction
			Execute_R_type(curr_ins);
	} else if(opcode == 1) {
		//process_others
			Execute_others(curr_ins);
	}


}

void Execute_R_type(uint32_t curr_ins) {
    uint32_t func = curr_ins & 0x3f;
    uint32_t rs = (curr_ins << 6) >> 27;
    uint32_t rt = (curr_ins << 11) >> 27;
    uint32_t rd = (curr_ins << 16) >> 27;
    uint32_t shamt = (curr_ins << 21) >> 27;
	
 switch (func) {
	case SRLV: NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rt]>>CURRENT_STATE.REGS[rs]; break;
	case SUB: NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rs] - CURRENT_STATE.REGS[rt]; break;
	case SLT: NEXT_STATE.REGS[rd]=((int32_t)CURRENT_STATE.REGS[rs] < (int32_t)CURRENT_STATE.REGS[rt])?1:0; break;
	case MTLO: NEXT_STATE.LO=CURRENT_STATE.REGS[rs]; break;
	case SRAV: NEXT_STATE.REGS[rd]=(int32_t)CURRENT_STATE.REGS[rt]>>((CURRENT_STATE.REGS[rs]<<27)>>27); break;
	case SUBU: NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rs] - CURRENT_STATE.REGS[rt]; break;
	case SLTU: NEXT_STATE.REGS[rd]=(CURRENT_STATE.REGS[rs] < CURRENT_STATE.REGS[rt])?1:0; break;
	case MULTU: int64_t product = CURRENT_STATE.REGS[rs]*CURRENT_STATE.REGS[rt];NEXT_STATE.HI=product>>32; NEXT_STATE.LO=product;break;
	case SLL: NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] << shamt; break;
	case JR: NEXT_STATE.PC = CURRENT_STATE.REGS[rs]; break;
	case AND: NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] & CURRENT_STATE.REGS[rt]; break;
	case MULT: NEXT_STATE.REGS[rd]=(int32_t)CURRENT_STATE.REGS[rs] * (int32_t)CURRENT_STATE.REGS[rt]; break;
	case DIV: NEXT_STATE.HI = (int32_t)CURRENT_STATE.REGS[rs] % (int32_t)CURRENT_STATE.REGS[rt]; NEXT_STATE.LO = (int32_t)CURRENT_STATE.REGS[rs] / (int32_t)CURRENT_STATE.REGS[rt]; break;
	case DIVU: NEXT_STATE.HI = CURRENT_STATE.REGS[rs] % CURRENT_STATE.REGS[rt]; NEXT_STATE.LO = CURRENT_STATE.REGS[rs] / CURRENT_STATE.REGS[rt]; break;
	case SRL: NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> shamt; break;
	case SRLV: NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> ((CURRENT_STATE.REGS[rs] << 27) >> 27); break;
	case JALR: NEXT_STATE.PC = CURRENT_STATE.REGS[rs];NEXT_STATE.REGS[rd] = CURRENT_STATE.PC + 4; break;
	case OR: NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]; break;
	case SRA: NEXT_STATE.REGS[rd] = (int32_t)CURRENT_STATE.REGS[rt] >> shamt; break;
	case ADD: NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt]; break;
	case ADDU: NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt]; break;
	case XOR: NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] ^ CURRENT_STATE.REGS[rt]; break;
	case MFLO: NEXT_STATE.REGS[rd] = CURRENT_STATE.LO; break;
	case SYSCALL:if (CURRENT_STATE.REGS[2] == 10) { RUN_BIT = 0;} break;
	case NOR: NEXT_STATE.REGS[rd] = !(CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]); break;
	case SLLV: NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] << ((CURRENT_STATE.REGS[rs] << 27) >> 27);; break;
	case MTHI: NEXT_STATE.HI = CURRENT_STATE.REGS[rs]; break;
 }
}


void Execute_R_type(uint32_t curr_ins) {
uint32_t opcode = curr_ins>>26;	
int32_t immediate = (curr_ins << 16) >> 16;
int32_t mem_addr +=CURRENT_STATE.REGS[rs] ;
int32_t mem_value = mem_read_32(mem_addr);
int32_t target = (curr_ins << 16) >> 14;

switch (opcode) {
	case J: NEXT_STATE.PC = (CURRENT_STATE.PC & 0xf0000000) + ((curr_ins << 2) & 0x0ffffffc); break;
	case ADDI: NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] + immediate; break;
	case XORI: NEXT_STATE.REGS[rt] = ((curr_ins << 16) >> 16) ^ CURRENT_STATE.REGS[rs]; break;
	case LHU: mem_value = mem_value << 16; mem_value = (uint32_t)mem_value >> 16; NEXT_STATE.REGS[rt] = mem_value; break;
	case BLTZAL: NEXT_STATE.REGS[31] = CURRENT_STATE.PC; if ((rs_value >> 31) < 0) {NEXT_STATE.PC = CURRENT_STATE.PC + target;} break;
	case JAL: NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4; NEXT_STATE.PC = (CURRENT_STATE.PC & 0xf0000000) + ((curr_ins << 2) & 0x0ffffffc); break;
	case ADDIU: NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] + immediate; break;
	case LUI: NEXT_STATE.REGS[rt] = immediate << 16; break;
	case SB: mem_write_32(mem_addr, ((CURRENT_STATE.REGS[rt]<<24)>>24)); break;
	case BGEZAL: NEXT_STATE.REGS[31] = CURRENT_STATE.PC; if ((CURRENT_STATE.REGS[rs] >> 31) == 0) { NEXT_STATE.PC = CURRENT_STATE.PC + target;} break;
	case BEQ: if (CURRENT_STATE.REGS[rs] == CURRENT_STATE.REGS[rt]) { NEXT_STATE.PC = CURRENT_STATE.PC + target;} break;
	case SLTI: if (rs_value < immediate) { NEXT_STATE.REGS[rt] = 1;} else { NEXT_STATE.REGS[rt] = 0; }; break;
	case LB:  NEXT_STATE.REGS[rt] = ((mem_value<<24)>>24); break;
	case SH: mem_write_32(mem_addr, ((CURRENT_STATE.REGS[rt]<<16)>>16)); break;
	case BNE: if (CURRENT_STATE.REGS[rs] != CURRENT_STATE.REGS[rt]) { NEXT_STATE.PC = CURRENT_STATE.PC + target;} break;
	case SLTIU: if ((uint32_t)rs_value < (uint32_t)immediate) {
                    NEXT_STATE.REGS[rt] = 1;
                }
                else {
                    NEXT_STATE.REGS[rt] = 0;
                } break;
	case LH: NEXT_STATE.REGS[rd] = !(CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]); break;
	case SW: NEXT_STATE.REGS[rd] = !(CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]); break;
	case BLEZ: NEXT_STATE.REGS[rd] = !(CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]); break;
	case ANDI: NEXT_STATE.REGS[rd] = !(CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]); break;
	case LW: NEXT_STATE.REGS[rd] = !(CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]); break;
	case BLTZ: NEXT_STATE.REGS[rd] = !(CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]); break;
	case BGTZ: NEXT_STATE.REGS[rd] = !(CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]); break;
	case ORI: NEXT_STATE.REGS[rd] = !(CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]); break;
	case LBU: NEXT_STATE.REGS[rd] = !(CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]); break;
	case BGEZ: NEXT_STATE.REGS[rd] = !(CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]); break;
	
}
}
