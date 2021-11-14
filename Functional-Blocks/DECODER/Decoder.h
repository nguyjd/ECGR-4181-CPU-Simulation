#ifndef __DECODER_H__
#define __DECODER_H__

#include "Instruction.h"
#include "Wire.h"

class Decoder
{

public:
	Decoder();
	Decoder(Instruction inst);

    // Debug print outs.
	void PrintControlLines();
	void PrintAssembly();

	void ConnectReadReg1(Wire* wire);
	void ConnectReadReg2(Wire* wire);
	void ConnectWriteEnable(Wire* wire);
	void ConnectWriteReg(Wire* wire);
	void ConnectWriteSel(Wire* wire);
	void ConnectImmi(Wire* wire);
	void ConnectImmi2(Wire* wire);
	void ConnectSign(Wire* wire);
	void ConnectALUSrc(Wire* wire);
	void ConnectALUop(Wire* wire);
	void ConnectALUdataSel(Wire* wire);
	void ConnectFlagControl(Wire* wire);
	void ConnectOffset(Wire* wire);
	void ConnectMemRead(Wire* wire);
	void ConnectMemWrite(Wire* wire);
	void ConnectMemSize(Wire* wire);
	void ConnectJump(Wire* wire);
	void ConnectAui(Wire* wire);
	void ConnectJalr(Wire* wire);

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
	Wire* readReg1;
	Wire* readReg2;
	
	// Enable writing to the registor file.
	Wire* writeEnable;
	
	// Five bits
	// The registor in the registor file being written to.
	Wire* writeReg;
	
	// Two bits
	// Control where the data comes from to write into the registor.
	Wire* writeSel;

	// 12-bits immediate
	Wire* immi;
	
	// 20-bits immediate
	Wire* immi2;

	// True if the data is signed.
	Wire* sign;

	// Select signal to control if the data is immediate or from the registor.
	Wire* ALUSrc;

	// Five bits
	Wire* ALUop;
	Wire* ALUdataSel;

	// Three bits
	Wire* flagControl;

	// 13 bits
	// The branch offset
	Wire* offset;

	// Enable reading from RAM.
	Wire* memRead;
	
	// Enable writing to the RAM
	Wire* memWrite;
	
	// Two bits
	// Size of the data requested.
	Wire* memSize;

	// Control if we are jumping.
	Wire* jump;
	
	// Control if we are using AUIPC or LUI
	Wire* aui;

	// Control if jumping with the registor or an offset.
	Wire* jalr;

};

#endif