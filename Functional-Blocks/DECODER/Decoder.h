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

	bool validState;
	Instruction currentInstruction;
	
	std::string assemblyInst;
	std::string opcode;

	// Set all the control signal varibles as bool or string of 0 or 1.
	
	// Five bits
	std::string readReg1;
	std::string readReg2;
	
	bool writeEnable;
	
	// Five bits
	std::string writeReg;
	
	// Two bits
	std::string writeSel;

	// 12 bits
	std::string immi;
	
	// 20 bits
	std::string immi2;

	bool sign;
	bool ALUSrc;

	// Five bits
	std::string ALUop;
	bool ALUdataSel;

	// Three bits
	std::string flagControl;

	// 13 bits
	std::string offset;

	bool memRead;
	bool memWrite;
	
	// Two bits
	std::string memSize;

	bool jump;
	bool aui;
	bool jalr;

};

#endif