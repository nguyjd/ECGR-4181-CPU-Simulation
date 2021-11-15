#include <iostream>
#include "Adder.h"
#include "Mux2to1.h"
#include "Mux4to1.h"
#include "SignExtend.h"
#include "ZeroExtend.h"
#include "ShiftLeft.h"
#include "RegisterFile.h"
#include "ProgramCounter.h"
#include "PipelineRegisters.h"
#include "ALU.h"
#include "DataMemory.h"
#include "Decoder.h"
#include <time.h>
#include "System.h"


std::vector<std::string> instructionsBin;
std::vector<std::string> instructionsNames;
void AddInstructions();
int BinToIndex(std::string input);

int main()
{

	Wire* CLK = new Wire(1);

	// ---------------------------IF WIRES----------------------------------------
	Wire* pcOut = new Wire(32);
	Wire* pcIn = new Wire(32);
	Wire* Four = new Wire(32);
	Four->SetWireData("00000000000000000000000000000100");
	Wire* offsetSignedEx = new Wire(32);
	Wire* branch_IF = new Wire(1);
	Wire* Mux1Output = new Wire(32);
	Wire* pcOutAdderResult = new Wire(32);
	Wire* jump_IF = new Wire(1);
	Wire* aui_IF = new Wire(1);
	Wire* branchOffset13bit_IF = new Wire(13);
	Wire* jalrMuxResult_IF = new Wire(32);

	Wire* instruction_IF = new Wire(32);



	
	//---------------------------ID WIRES------------------------------------------
	Wire* jalr = new Wire(1);
	Wire* writeSel_ID = new Wire(2);
	Wire* writeReg = new Wire(5);
	Wire* writeData_ID = new Wire(32);
	Wire* writeEnable = new Wire(1);
	Wire* readReg1 = new Wire(5);
	Wire* readReg2 = new Wire(5);
	
		// Decoder Values
	Wire* jump_ID = new Wire(1);
	Wire* aui_ID = new Wire(1);
	Wire* branchOffset13bit_ID = new Wire(13);
	Wire* memSize_ID = new Wire(2);
	Wire* memWrite_ID = new Wire(1);
	Wire* memRead_ID = new Wire(1);
	Wire* Signed_ID = new Wire(1);
	Wire* dataSel = new Wire(1);
	Wire* aluOp_ID = new Wire(5);
	Wire* dataSel_ID = new Wire(1);
	Wire* ALUSrc = new Wire(1);
	Wire* immi20BitSmile = new Wire(20);
	Wire* immediateDecOut = new Wire(12);
	Wire* immediateSignExtended = new Wire(32);

	Wire* reg1_ID = new Wire(32);
	Wire* reg2_ID = new Wire(32);

	Wire* inputB_ID = new Wire(32);

	Wire* instruction_ID = new Wire(32);
	
	Wire* flag = new Wire(3);


	// ---------------------------EX WIRES-------------------------------------------------
	
	Wire* aluOp_EX = new Wire(5);
	Wire* dataSel_EX = new Wire(1);
	Wire* writeSel_EX = new Wire(2);
	Wire* Signed_EX = new Wire(1);
	Wire* ALUoutput = new Wire(32);
	Wire* branchSignal = new Wire(1);
	Wire* inputB_EX = new Wire(32);

	Wire* reg1_EX = new Wire(32);
	Wire* reg2_EX = new Wire(32);

	Wire* ToReg = new Wire(32);
	Wire* ToMem = new Wire(32);
	Wire* memWrite_EX = new Wire(1);
	Wire* memRead_EX = new Wire(1);
	Wire* memSize_EX = new Wire(2);


	// ---------------------------STORE Wires (MEM/WB)------------------------------------------------------------

	Wire* ALUoutput_WB = new Wire(32);

	Wire* LUIWire = new Wire(32);
	Wire* JALWire = new Wire(32);

	// Input Wires
	Wire* memSize = new Wire(2);
	Wire* memRead = new Wire(1);
	Wire* memWrite = new Wire(1);
	Wire* dataIn = new Wire(32);
	Wire* memAddress = new Wire(32);

	// Output Wires
	Wire* outputEightBits = new Wire(8);
	Wire* outputSixteenBits = new Wire(16);
	Wire* outputThirtyTwoBits = new Wire(32);

	Wire* regData_wb = new Wire(32);
	Wire* writeSel_wb = new Wire(2);


	//-----------------------------IF Components---------------------------------------

	// Processor Blocks
	Adder* PCadder = new Adder(pcOut, Mux1Output, pcIn);
	Mux2to1* branchMux = new Mux2to1(Four, offsetSignedEx, branchSignal, Mux1Output);
	ProgramCounter* PC = new ProgramCounter(pcIn, pcOut, CLK);

	SignExtend* sign = new SignExtend(branchOffset13bit_IF, offsetSignedEx);

	// TODO: Convert pcOut to a indexalbe value to get the instruction
	
	//Adder* adder2 = new Adder();
	//ShiftLeft* shift12 = new ShiftLeft();
	//Mux2to1* auiMux = new Mux2to1();


	PipelineRegisters* IFID = new PipelineRegisters();
	IFID->ConnectCLK(CLK);
	IFID->ConnectInputAndOutputPair(branchOffset13bit_ID, branchOffset13bit_IF);
	IFID->ConnectInputAndOutputPair(instruction_IF, instruction_ID);


	//-----------------------------ID Components---------------------------------------

	//TODO: Connect all the wires to the decoder.
	Decoder* decode = new Decoder();

	decode->ConnectALUdataSel(dataSel_ID);
	decode->ConnectALUop(aluOp_ID);
	decode->ConnectALUSrc(ALUSrc);
	decode->ConnectAui(aui_ID);
	decode->ConnectFlagControl(flag);
	decode->ConnectImmi(immediateDecOut);
	decode->ConnectImmi2(immi20BitSmile);
	decode->ConnectJalr(jalr);
	decode->ConnectJump(jump_ID);
	decode->ConnectMemRead(memRead_ID);
	decode->ConnectMemSize(memSize_ID);
	decode->ConnectMemWrite(memWrite_ID);
	decode->ConnectOffset(branchOffset13bit_ID);
	decode->ConnectReadReg1(readReg1);
	decode->ConnectReadReg2(readReg2);
	decode->ConnectSign(Signed_ID);
	decode->ConnectWriteEnable(writeEnable);
	decode->ConnectWriteReg(writeReg);
	decode->ConnectWriteSel(writeSel_ID);

	RegisterFile* reg = new RegisterFile(readReg1, readReg2, reg1_ID, reg2_ID, writeEnable, writeReg, writeData_ID);
	SignExtend* immiSignedEx = new SignExtend(immediateDecOut, immediateSignExtended);

	Mux2to1* inputBMux = new Mux2to1(reg2_ID, immediateSignExtended, ALUSrc, inputB_ID);

	PipelineRegisters* IDEX = new PipelineRegisters();

	IDEX->ConnectCLK(CLK);
	IDEX->ConnectInputAndOutputPair(reg1_ID, reg1_EX);
	IDEX->ConnectInputAndOutputPair(reg2_ID, reg2_EX);
	IDEX->ConnectInputAndOutputPair(inputB_ID, inputB_EX);
	IDEX->ConnectInputAndOutputPair(aluOp_ID, aluOp_EX);
	IDEX->ConnectInputAndOutputPair(dataSel_ID, dataSel_EX);
	IDEX->ConnectInputAndOutputPair(memRead_ID, memRead_EX);
	IDEX->ConnectInputAndOutputPair(memWrite_ID, memWrite_EX);
	IDEX->ConnectInputAndOutputPair(memSize_ID, memSize_EX);
	IDEX->ConnectInputAndOutputPair(writeSel_ID, writeSel_EX);

	//-----------------------------EX Components---------------------------------------

	ALU* alu = new ALU(reg1_EX, inputB_EX, aluOp_EX, ALUoutput, branchSignal);
	

	PipelineRegisters* EXWB = new PipelineRegisters();
	EXWB->ConnectCLK(CLK);
	EXWB->ConnectInputAndOutputPair(ToReg, ALUoutput_WB);
	EXWB->ConnectInputAndOutputPair(ToMem, memAddress);
	EXWB->ConnectInputAndOutputPair(memRead_EX, memRead);
	EXWB->ConnectInputAndOutputPair(memWrite_EX, memWrite);
	EXWB->ConnectInputAndOutputPair(reg2_EX, dataIn);
	EXWB->ConnectInputAndOutputPair(memSize_EX, memSize);
	EXWB->ConnectInputAndOutputPair(writeSel_EX, writeSel_wb);


	//-----------------------------MEM/WB Components---------------------------------------

	DataMemory* ram = new DataMemory(memSize, memRead, memWrite, dataIn, memAddress, outputEightBits, outputSixteenBits, outputThirtyTwoBits);
	
	Mux4to1* dataWriteMux = new Mux4to1(ALUoutput_WB, outputThirtyTwoBits, LUIWire, JALWire, writeSel_wb, writeData_ID);



	// CPU CODE
	AddInstructions();
	int index = 0;

	CLK->SetWireData("1");

	unsigned long long int clockCount = 0;
	// Main loop
	while (true)
	{

		time_t seconds = time(0);

		IFID->Update();
		IDEX->Update();
		EXWB->Update();


		PC->Update();
		index = BinToIndex(pcOut->GetWireDataStr()) / 4;
		sign->Update();
		branchMux->Update();


		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

		std::cout << "INSTRUCTION FETCH STAGE" << std::endl;
		std::cout << "Instuction Name: \t" << instructionsNames[index] << std::endl;
		std::cout << "PC: \t\t" << pcOut->GetWireDataStr() << std::endl;
		std::cout << "Current Clock Cycle: \t" << clockCount<< std::endl;
		

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

		PCadder->Update();


		// Fetch the instruction.
		if (index < instructionsBin.size())
		{

			instruction_IF->SetWireData(instructionsBin[index]);

		}


		// ID

		decode->NextInstruction(instruction_ID->GetWireDataStr());
		decode->PrintAssembly();
		decode->PrintControlLines();

		reg->Update();
		reg->PrintRegisters();
		immiSignedEx->Update();
		inputBMux->Update();


		//EX
		alu->Update();

		sign->Update();
		branchMux->Update();

		PCadder->Update();

		alu->CheckBranch();


		if (dataSel_EX->GetWireDataStr().compare("0") == 0)
		{

			ToReg->SetWireData(ALUoutput->GetWireDataStr());

		}
		else if (dataSel_EX->GetWireDataStr().compare("1") == 0)
		{

			ToMem->SetWireData(ALUoutput->GetWireDataStr());

		}


		//WB
		ram->Update();
		ram->PrintMemory();
		dataWriteMux->Update();
		std::cout << branchSignal->GetWireDataStr() << std::endl;
		

		// Delay for one second.
		time_t currentTime = time(0);
		while (seconds == currentTime)
		{

			currentTime = time(0);

		}

		clockCount++;

	}

	return 0;

}

void AddInstructions()
{

	// Load - Data Hazard
	instructionsBin.push_back("00000000000000010010000010000011");
	instructionsBin.push_back("00000000000000000000000000000000");
	instructionsBin.push_back("00000000000000000000000000000000");
	instructionsNames.push_back("lw x1, 0(x2)");
	instructionsNames.push_back("no op");
	instructionsNames.push_back("no op");


	// ADD
	instructionsBin.push_back("00000000001100001000001010110011");
	instructionsBin.push_back("00000000000000000000000000000000");
	instructionsNames.push_back("add x5, x1, x3");
	instructionsNames.push_back("no op");

	// Store
	instructionsBin.push_back("00000000001000101010000000100011");
	instructionsBin.push_back("00000000000000000000000000000000");
	instructionsNames.push_back("s2 x5, 0(x2)");
	instructionsNames.push_back("no op");
	
	//ADDI
	instructionsBin.push_back("11111111110000010000000100010011");
	instructionsNames.push_back("addi x2, x2, -4");
	
	// Stall the pipeline
	instructionsBin.push_back("00000000000000000000000000000000");
	instructionsBin.push_back("00000000000000000000000000000000");
	instructionsBin.push_back("00000000000000000000000000000000");
	instructionsNames.push_back("no op");
	instructionsNames.push_back("no op");
	instructionsNames.push_back("no op");

	// Branch
	instructionsBin.push_back("11111100001000011001011011100011");
	instructionsNames.push_back("BNE x2, x3, loop");

	instructionsBin.push_back("11111111111111111111111111111111");
	instructionsNames.push_back("Halt");

}

int BinToIndex(std::string input)
{

	int poweroftwo = 1;
	int results = 0;

	// Up to MSB
	for (int i = input.size() - 1; i > 0; i--)
	{

		char num = input[i] - '0';

		results += num * poweroftwo;

		poweroftwo *= 2;

	}

	results -= (input[0] * poweroftwo);

	return results;

}
