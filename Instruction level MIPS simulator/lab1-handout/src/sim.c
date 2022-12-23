#include <stdio.h>
#include "shell.h"

#define SRLV 6
#define SUB 34
#define SLT 42
#define MTLO 19
#define SRAV 7
#define SUBU 35
#define SLTU 43
#define MULTU 25
#define SLL 0
#define JR 8
#define AND 36
#define MULT 24
#define DIV 26
#define DIVU 27
#define SRL 2
#define JALR 9
#define OR 37
#define SRA 3
#define ADD 32
#define XOR 38
#define MFLO 18
#define SYSCALL 12
#define NOR 39
#define SLLV 4
#define MTHI 17
#define MFHI 16
#define ADDU 33

#define J 2
#define ADDI 8
#define XORI 14
#define LHU 37
#define BLTZAL 1
#define JAL 3
#define ADDIU 9
#define LUI 15
#define SB 40
#define BGEZAL 1
#define BEQ 4
#define SLTI 10
#define LB 32
#define SH 41
#define BNE 5
#define SLTIU 11
#define LH 33
#define SW 43
#define BLEZ 6
#define ANDI 12
#define LW 35
#define BLTZ 1
#define BGTZ 7
#define ORI 13
#define LBU 36
#define BGEZ 1


void Execute_R_type(uint32_t curr_ins);
void Execute_others(uint32_t curr_ins);

void process_instruction()
{   int a;
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
	} else {
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
	case MFHI: NEXT_STATE.REGS[rd] = CURRENT_STATE.HI;  break;
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


void Execute_others(uint32_t curr_ins) {
	uint32_t opcode = curr_ins>>26;	
	int32_t immediate = (curr_ins << 16);
        immediate = immediate >> 16;
        uint32_t rs = (curr_ins << 6) >> 27;
        uint32_t rt = (curr_ins << 11) >> 27;
        uint32_t rd = (curr_ins << 16) >> 27;
	int32_t mem_addr =immediate + CURRENT_STATE.REGS[rs] ;
	int32_t mem_value = mem_read_32(mem_addr);
	int32_t target = curr_ins << 16; 
	target = target >> 14;
        //intf("%d",opcode);	
	switch (opcode) {
	case J: NEXT_STATE.PC = (CURRENT_STATE.PC & 0xf0000000) + ((curr_ins << 2) & 0x0ffffffc); break;
	case ADDI: NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] + immediate; break;
	case XORI: NEXT_STATE.REGS[rt] = ((curr_ins << 16) >> 16) ^ CURRENT_STATE.REGS[rs]; break;
	case LHU: mem_value = mem_value << 16; mem_value = (uint32_t)mem_value >> 16; NEXT_STATE.REGS[rt] = mem_value; break;
	case JAL: NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4; NEXT_STATE.PC = (CURRENT_STATE.PC & 0xf0000000) + ((curr_ins << 2) & 0x0ffffffc); break;
	case ADDIU: NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] + immediate; break;
	case LUI: NEXT_STATE.REGS[rt] = immediate << 16; break;
	case SB: mem_write_32(mem_addr, ((CURRENT_STATE.REGS[rt]<<24)>>24)); break;
	case 1:
	switch(rt) {
	//BGEZAL
	case 17: NEXT_STATE.REGS[31] = CURRENT_STATE.PC; if ((CURRENT_STATE.REGS[rs] >> 31) == 0) { NEXT_STATE.PC = CURRENT_STATE.PC + target;}  break;
	//BGEZ
	case 1: if ((CURRENT_STATE.REGS[rs] == 0) || (CURRENT_STATE.REGS[rs] >> 31) == 0) { NEXT_STATE.PC = CURRENT_STATE.PC + target;} break;
        //BLTZ
	case 0: if ((CURRENT_STATE.REGS[rs] >> 31) == -1) { NEXT_STATE.PC = CURRENT_STATE.PC + target; } break;
	//BLTZAL
	case 16: NEXT_STATE.REGS[31] = CURRENT_STATE.PC; if ((CURRENT_STATE.REGS[rs]>> 31) < 0) {NEXT_STATE.PC = CURRENT_STATE.PC + target;} break;
	}
	break;
	case BEQ: if (CURRENT_STATE.REGS[rs] == CURRENT_STATE.REGS[rt]) { NEXT_STATE.PC = CURRENT_STATE.PC + target;} break;
	case SLTI: if (CURRENT_STATE.REGS[rs] < immediate) { NEXT_STATE.REGS[rt] = 1;} else { NEXT_STATE.REGS[rt] = 0; }; break;
	case LB:  NEXT_STATE.REGS[rt] = ((mem_value<<24)>>24); break;
	case SH: mem_write_32(mem_addr, ((CURRENT_STATE.REGS[rt]<<16)>>16)); break;
	case BNE: if (CURRENT_STATE.REGS[rs] != CURRENT_STATE.REGS[rt]) { NEXT_STATE.PC = CURRENT_STATE.PC + target;} break;
	case SLTIU: if ((uint32_t)CURRENT_STATE.REGS[rs] < (uint32_t)immediate) { NEXT_STATE.REGS[rt] = 1;} else {NEXT_STATE.REGS[rt] = 0;} break;
	case LH: NEXT_STATE.REGS[rt] = ((mem_value<<16)>>16); break;
	case SW: mem_write_32(mem_addr, CURRENT_STATE.REGS[rt]); break;
	case BLEZ: if ((CURRENT_STATE.REGS[rs] == 0) || (CURRENT_STATE.REGS[rs] >> 31) == -1) { NEXT_STATE.PC = CURRENT_STATE.PC + target;} break;
	case ANDI: NEXT_STATE.REGS[rt] = ((curr_ins << 16) >> 16) & CURRENT_STATE.REGS[rs]; break;
	case LW: NEXT_STATE.REGS[rt] = mem_value; break;
	case BGTZ: if ((CURRENT_STATE.REGS[rs] != 0) && ((CURRENT_STATE.REGS[rs] >> 31) == 0)) { NEXT_STATE.PC = CURRENT_STATE.PC + target;} break;
	case ORI: NEXT_STATE.REGS[rt] = immediate | CURRENT_STATE.REGS[rs]; break;
	case LBU:  mem_value = mem_value << 24; mem_value = (uint32_t)mem_value >> 24; NEXT_STATE.REGS[rt] = mem_value; break;
	
}
}
