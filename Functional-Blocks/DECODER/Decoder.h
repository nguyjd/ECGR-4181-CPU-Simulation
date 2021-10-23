#ifndef __DECODER_H__
#define __DECODER_H__

#include "Instruction.h"
#include <string>
#include <vector>

class Decoder
{

public:
	Decoder();
	Decoder(Instruction inst);

    // Debug print outs.
	void PrintControlLines();
	void PrintAssembly();

    // The function to decode the next instruction.
	void NextInstruction(Instruction inst);

private:

	void DecodeInstruction();

	// True if the current instruction is valid.
	bool validState;
	Instruction currentInstruction;
	
	// Hold the assembly code of the current instruction.
	std::string assemblyInst;
	
	// The opcode of the instruction.
	std::string opcode;

	// Set all the control signal varibles as bool or string of 0 or 1.
	// Both readReg1 and 2 are five bits
	std::string readReg1;
	std::string readReg2;
	
	// Enable writing to the registor file.
	bool writeEnable;
	
	// Five bits
	// The registor in the registor file being written to.
	std::string writeReg;
	
	// Two bits
	// Control where the data comes from to write into the registor.
	std::string writeSel;

	// 12-bits immediate
	std::string immi;
	
	// 20-bits immediate
	std::string immi2;

	// True if the data is signed.
	bool sign;

	// Select signal to control if the data is immediate or from the registor.
	bool ALUSrc;

	// Five bits
	std::string ALUop;
	bool ALUdataSel;

	// Three bits
	std::string flagControl;

	// 13 bits
	// The branch offset
	std::string offset;

	// Enable reading from RAM.
	bool memRead;
	
	// Enable writing to the RAM
	bool memWrite;
	
	// Two bits
	// Size of the data requested.
	std::string memSize;

	// Control if we are jumping.
	bool jump;
	
	// Control if we are using AUIPC or LUI
	bool aui;

	// Control if jumping with the registor or an offset.
	bool jalr;

};

#endif