#include <stdio.h>
#include "shell.h"

void process_instruction()
{
    /* execute one instruction here. You should use CURRENT_STATE and modify
     * values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
     * access memory. */
	//fetch instrcution from current PC
	uint32_t curr_ins = mem_read_32(CURRENT_STATE.PC);
	//extracting opcode	
	uint32_t opcode = curr_ins>>26;

	if(opcode == 0) {
		//R-Type instruction
			Execute_R_type(curr_ins);
	} else if(opcode == 1) {
		//process_others
	}


}

void Execute_R_type(uint32_t curr_ins) {

	switch()


}
