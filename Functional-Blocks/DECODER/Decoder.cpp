#include "Decoder.h"

Decoder::Decoder()
{

	readReg1 = nullptr;
	readReg2 = nullptr;
	writeEnable = nullptr;
	writeReg = nullptr;
	writeSel = nullptr;
	immi = nullptr;
	immi2 = nullptr;
	ALUSrc = nullptr;
	sign = nullptr;
	ALUop = nullptr;
	ALUdataSel = nullptr;
	flagControl = nullptr;
	offset = nullptr;
	memRead = nullptr;
	memWrite = nullptr;
	memSize = nullptr;
	jump = nullptr;
	aui = nullptr;

	validState = false;

}

Decoder::Decoder(Instruction inst)
{

	readReg1 = nullptr;
	readReg2 = nullptr;
	writeEnable = nullptr;
	writeReg = nullptr;
	writeSel = nullptr;
	immi = nullptr;
	immi2 = nullptr;
	ALUSrc = nullptr;
	sign = nullptr;
	ALUop = nullptr;
	ALUdataSel = nullptr;
	flagControl = nullptr;
	offset = nullptr;
	memRead = nullptr;
	memWrite = nullptr;
	memSize = nullptr;
	jump = nullptr;
	aui = nullptr;

	validState = false;

    // Check the string is valid. If we dont, we can have array access errors.
	if (inst.IsInstructionValid())
	{
		
		currentInstruction = inst;
		DecodeInstruction();

	}

}

void Decoder::PrintControlLines()
{

	std::cout << "-----------------------------Control Signals---------------------------------------" << std::endl;
	std::cout << "readReg1: " << readReg1->GetWireDataStr() << std::endl;
	std::cout << "readReg2: " << readReg2->GetWireDataStr() << std::endl;
	std::cout << "writeEnable: " << writeEnable->GetWireDataStr() << std::endl;
	std::cout << "writeReg: " << writeReg->GetWireDataStr() << std::endl;
	std::cout << "writeSel: " << writeSel->GetWireDataStr() << std::endl;
	std::cout << "immi: " << immi->GetWireDataStr() << std::endl;
	std::cout << "immi2: " << immi2->GetWireDataStr() << std::endl;
	std::cout << "ALUSrc: " << ALUSrc->GetWireDataStr() << std::endl;
	std::cout << "sign: " << sign->GetWireDataStr() << std::endl;
	std::cout << "ALUop: " << ALUop->GetWireDataStr() << std::endl;
	std::cout << "ALUdataSel: " << ALUdataSel->GetWireDataStr() << std::endl;
	std::cout << "flagControl: " << flagControl->GetWireDataStr() << std::endl;
	std::cout << "offset: " << offset->GetWireDataStr() << std::endl;
	std::cout << "memRead: " << memRead->GetWireDataStr() << std::endl;
	std::cout << "memWrite: " << memWrite->GetWireDataStr() << std::endl;
	std::cout << "memSize: " << memSize->GetWireDataStr() << std::endl;
	std::cout << "jump: " << jump->GetWireDataStr() << std::endl;
	std::cout << "aui: " << aui->GetWireDataStr() << std::endl;
	std::cout << "-----------------------------------------------------------------------------------" << std::endl;

}

void Decoder::PrintAssembly()
{

	if (validState)
	{

		std::cout << "Instruction: " << assemblyInst << std::endl;

	}
	else
	{

		std::cout << "The instruction was not found or invalid." << std::endl;

	}

}

void Decoder::ConnectReadReg1(Wire* wire)
{

	// Set the wire
	readReg1 = wire;

}

void Decoder::ConnectReadReg2(Wire* wire)
{

	// Set the wire
	readReg2 = wire;

}

void Decoder::ConnectWriteEnable(Wire* wire)
{

	// Set the wire
	writeEnable = wire;

}

void Decoder::ConnectWriteReg(Wire* wire)
{

	// Set the wire
	writeReg = wire;

}

void Decoder::ConnectWriteSel(Wire* wire)
{

	// Set the wire
	writeSel = wire;

}

void Decoder::ConnectImmi(Wire* wire)
{

	// Set the wire
	immi = wire;

}

void Decoder::ConnectImmi2(Wire* wire)
{

	// Set the wire
	immi2 = wire;

}

void Decoder::ConnectSign(Wire* wire)
{

	// Set the wire
	sign = wire;

}

void Decoder::ConnectALUSrc(Wire* wire)
{

	// Set the wire
	ALUSrc = wire;

}

void Decoder::ConnectALUop(Wire* wire)
{

	// Set the wire
	ALUop = wire;

}

void Decoder::ConnectALUdataSel(Wire* wire)
{

	// Set the wire
	ALUdataSel = wire;

}

void Decoder::ConnectFlagControl(Wire* wire)
{

	// Set the wire
	flagControl = wire;

}

void Decoder::ConnectOffset(Wire* wire)
{

	// Set the wire
	offset = wire;

}

void Decoder::ConnectMemRead(Wire* wire)
{

	memRead = wire;

}

void Decoder::ConnectMemWrite(Wire* wire)
{

	// Set the wire
	memWrite = wire;

}

void Decoder::ConnectMemSize(Wire* wire)
{

	// Set the wire
	memSize = wire;

}

void Decoder::ConnectJump(Wire* wire)
{

	// Set the wire
	jump = wire;

}

void Decoder::ConnectAui(Wire* wire)
{

	// Set the wire
	aui = wire;

}

void Decoder::ConnectJalr(Wire* wire)
{

	// Set the wire
	jalr = wire;

}

void Decoder::NextInstruction(Instruction inst)
{

    
	validState = false;

    // Check the string is valid. If we dont, we can have array access errors.
	if (inst.IsInstructionValid())
	{
		
		currentInstruction = inst;
		DecodeInstruction();

	}

}

void Decoder::DecodeInstruction()
{

	std::string instruction = currentInstruction.GetInstructionStr();
	opcode = instruction.substr(25, 7);

	// Identify opcodes.
	// ALU Operations
	if (opcode.compare("0110011") == 0)
	{

		std::string func7 = instruction.substr(0, 7);
		std::string func3 = instruction.substr(17, 3);
		
		readReg1->SetWireData(instruction.substr(7, 5));
		readReg2->SetWireData(instruction.substr(12, 5));
		writeEnable->SetWireData("1");
		writeReg->SetWireData(instruction.substr(20, 5));
		ALUdataSel->SetWireData("0");
		ALUSrc->SetWireData("0");
		writeSel->SetWireData("00");

		// Default states.
		immi->SetWireData("000000000000");
		immi2->SetWireData("00000000000000000000");
		flagControl->SetWireData("000");
		offset->SetWireData("0000000000000");
		memRead->SetWireData("0");
		memWrite->SetWireData("0");
		memSize->SetWireData("00");
		jump->SetWireData("0");
		aui->SetWireData("0");
		sign->SetWireData("1");

		// ADD
		if (func7.compare("0000000") == 0 && func3.compare("000") == 0)
		{

			validState = true;
			assemblyInst = "ADD";
			ALUop->SetWireData("00000");

		}

		// SUB
		if (func7.compare("0100000") == 0 && func3.compare("000") == 0)
		{

			validState = true;
			assemblyInst = "SUB";
			ALUop->SetWireData("00001");

		}

		// SLL
		if (func7.compare("0000000") == 0 && func3.compare("001") == 0)
		{

			validState = true;
			assemblyInst = "SLL";
			ALUop->SetWireData("00010");

		}

		// SLT
		if (func7.compare("0000000") == 0 && func3.compare("010") == 0)
		{

			validState = true;
			assemblyInst = "SLT";
			ALUop->SetWireData("00011");

		}

		// SLTU
		if (func7.compare("0000000") == 0 && func3.compare("011") == 0)
		{

			validState = true;
			assemblyInst = "SLTU";
			ALUop->SetWireData("00011");

		}

		// XOR
		if (func7.compare("0000000") == 0 && func3.compare("100") == 0)
		{

			validState = true;
			assemblyInst = "XOR";
			ALUop->SetWireData("00100");

		}

		// SRL
		if (func7.compare("0000000") == 0 && func3.compare("101") == 0)
		{

			validState = true;
			assemblyInst = "SRL";
			ALUop->SetWireData("00101");

		}

		// SRA
		if (func7.compare("0100000") == 0 && func3.compare("101") == 0)
		{

			validState = true;
			assemblyInst = "SRA";
			ALUop->SetWireData("00110");

		}

		// OR
		if (func7.compare("0000000") == 0 && func3.compare("110") == 0)
		{

			validState = true;
			assemblyInst = "OR";
			ALUop->SetWireData("00111");

		}

		// AND
		if (func7.compare("0000000") == 0 && func3.compare("111") == 0)
		{

			validState = true;
			assemblyInst = "AND";
			ALUop->SetWireData("01000");

		}

		// MUL
		if (func7.compare("0000001") == 0 && func3.compare("000") == 0)
		{

			validState = true;
			assemblyInst = "MUL";
			ALUop->SetWireData("10000");

		}

		// MULH
		if (func7.compare("0000001") == 0 && func3.compare("001") == 0)
		{

			validState = true;
			assemblyInst = "MULH";
			ALUop->SetWireData("10001");

		}

		// MULHSU
		if (func7.compare("0000001") == 0 && func3.compare("010") == 0)
		{

			validState = true;
			assemblyInst = "MULHSU";
			ALUop->SetWireData("10010");

		}

		// MULHU
		if (func7.compare("0000001") == 0 && func3.compare("011") == 0)
		{

			validState = true;
			assemblyInst = "MULHU";
			ALUop->SetWireData("10011");

		}

		// DIV
		if (func7.compare("0000001") == 0 && func3.compare("100") == 0)
		{

			validState = true;
			assemblyInst = "DIV";
			ALUop->SetWireData("10100");

		}

		// DIVU
		if (func7.compare("0000001") == 0 && func3.compare("101") == 0)
		{

			validState = true;
			assemblyInst = "DIVU";
			ALUop->SetWireData("11100");

		}

		// REM
		if (func7.compare("0000001") == 0 && func3.compare("110") == 0)
		{

			validState = true;
			assemblyInst = "REM";
			ALUop->SetWireData("11101");

		}

		// REMU
		if (func7.compare("0000001") == 0 && func3.compare("111") == 0)
		{

			validState = true;
			assemblyInst = "REMU";
			ALUop->SetWireData("11110");

		}

	}

	// ALU Immediate Operations
	if (opcode.compare("0010011") == 0)
	{

        // Only used for SLLI SRLI SRAI
		std::string func7 = instruction.substr(0, 7);
		std::string func3 = instruction.substr(17, 3);

		immi->SetWireData(instruction.substr(0, 12));
		readReg1->SetWireData(instruction.substr(12, 5));
		writeEnable->SetWireData("1");
		writeReg->SetWireData(instruction.substr(20, 5));
		ALUSrc->SetWireData("1");
		ALUdataSel->SetWireData("0");
		writeSel->SetWireData("00");

		// Default states.
		readReg2->SetWireData("00000");
		immi2->SetWireData("00000000000000000000");
		flagControl->SetWireData("000");
		offset->SetWireData("0000000000000");
		memRead->SetWireData("0");
		memWrite->SetWireData("0");
		memSize->SetWireData("00");
		jump->SetWireData("0");
		aui->SetWireData("0");

		// ADDI
		if ( func3.compare("000") == 0)
		{

			validState = true;
			assemblyInst = "ADDI";
			sign->SetWireData("1");
			ALUop->SetWireData("00000");

		}

		// SLTI
		if (func3.compare("010") == 0)
		{

			validState = true;
			assemblyInst = "SLTI";
			sign->SetWireData("1");
			ALUop->SetWireData("00011");

		}

		// SLTIU
		if (func3.compare("011") == 0)
		{

			validState = true;
			assemblyInst = "SLTIU";
			sign->SetWireData("0");
			ALUop->SetWireData("01011");

		}

		// XORI
		if (func3.compare("100") == 0)
		{

			validState = true;
			assemblyInst = "XORI";
			sign->SetWireData("1");
			ALUop->SetWireData("00100");

		}

		// ORI
		if (func3.compare("110") == 0)
		{

			validState = true;
			assemblyInst = "ORI";
			sign->SetWireData("1");
			ALUop->SetWireData("00111");

		}

		// ANDI
		if (func3.compare("111") == 0)
		{

			validState = true;
			assemblyInst = "ANDI";
			sign->SetWireData("1");
			ALUop->SetWireData("01000");

		}

        // SLLI
		if (func7.compare("0000000") == 0 && func3.compare("001") == 0)
		{

			validState = true;
			assemblyInst = "SLLI";

			sign->SetWireData("1");
			ALUop->SetWireData("01001");

		}

        // SRLI
		if (func7.compare("0000000") == 0 && func3.compare("101") == 0)
		{

			validState = true;
			assemblyInst = "SRLI";

			sign->SetWireData("1");
			ALUop->SetWireData("01010");

		}

        // SRAI
		if (func7.compare("0100000") == 0 && func3.compare("101") == 0)
		{

			validState = true;
			assemblyInst = "SRAI";

			sign->SetWireData("1");
			ALUop->SetWireData("01100");

		}

	}

	// Load Operations
	if (opcode.compare("0000011") == 0)
	{ 

		std::string func3 = instruction.substr(17, 3);

		writeSel->SetWireData("01");
		writeEnable->SetWireData("1");
		immi->SetWireData(instruction.substr(0, 12));
		readReg1->SetWireData(instruction.substr(12, 5));
		writeReg->SetWireData(instruction.substr(20, 5));
		ALUSrc->SetWireData("1");
		ALUdataSel->SetWireData("1");
		memRead->SetWireData("1");
		memRead->SetWireData("0");

		// Default states.
		readReg2->SetWireData("00000");
		immi2->SetWireData("00000000000000000000");
		flagControl->SetWireData("000");
		offset->SetWireData("0000000000000");
		jump->SetWireData("0");
		aui->SetWireData("0");

		// LB
		if (func3.compare("000") == 0)
		{

			validState = true;
			assemblyInst = "LB";

			ALUop->SetWireData("01111");
			memSize->SetWireData("00");
			sign->SetWireData("1");

		}

		// LH
		if (func3.compare("001") == 0)
		{

			validState = true;
			assemblyInst = "LH";

			ALUop->SetWireData("01111");
			memSize->SetWireData("01");
			sign->SetWireData("1");

		}

		// LW
		if (func3.compare("010") == 0)
		{

			validState = true;
			assemblyInst = "LW";

			ALUop->SetWireData("01111");
			memSize->SetWireData("10");
			sign->SetWireData("1");

		}

		// LBU
		if (func3.compare("100") == 0)
		{

			validState = true;
			assemblyInst = "LBU";

			ALUop->SetWireData("01111");
			memSize->SetWireData("00");
			sign->SetWireData("0");

		}

		// LHU
		if (func3.compare("101") == 0)
		{

			validState = true;
			assemblyInst = "LHU";

			ALUop->SetWireData("01111");
			memSize->SetWireData("01");
			sign->SetWireData("0");

		}

		// LWU
		if (func3.compare("110") == 0)
		{

			validState = true;
			assemblyInst = "LWU";

			ALUop->SetWireData("01111");
			memSize->SetWireData("10");
			sign->SetWireData("0");

		}

	}

	// Store Operations
	if (opcode.compare("0100011") == 0)
	{

		std::string func3 = instruction.substr(17, 3);

		immi->SetWireData(instruction.substr(0, 7) + instruction.substr(20, 5));
		readReg1->SetWireData(instruction.substr(7, 5));
		readReg2->SetWireData(instruction.substr(12, 5));
		ALUSrc->SetWireData("1");
		ALUdataSel->SetWireData("1");
		sign->SetWireData("1");
		memRead->SetWireData("0");
		memWrite->SetWireData("1");

		// Default states.
		writeEnable->SetWireData("0");
		writeReg->SetWireData("00000");
		writeSel->SetWireData("00");
		immi2->SetWireData("00000000000000000000");
		jump->SetWireData("0");
		aui->SetWireData("0");
		flagControl->SetWireData("000");
		offset->SetWireData("0000000000000");

		// SB
		if (func3.compare("000") == 0)
		{

			validState = true;
			assemblyInst = "SB";

			ALUop->SetWireData("11011");
            memSize->SetWireData("00");

		}

		// SH
		if (func3.compare("001") == 0)
		{

			validState = true;
			assemblyInst = "SH";

			ALUop->SetWireData("11011");
            memSize->SetWireData("01");

		}

		// SW
		if (func3.compare("010") == 0)
		{

			validState = true;
			assemblyInst = "SW";

			ALUop->SetWireData("11011");
            memSize->SetWireData("01");

		}

	}

	// Branch Operations
	if (opcode.compare("1100011") == 0)
	{

		std::string func3 = instruction.substr(17, 3);
		offset->SetWireData(instruction.substr(0, 1) + instruction.substr(24, 1) + instruction.substr(1, 6) + instruction.substr(20, 4) + "0");
		readReg1->SetWireData(instruction.substr(7, 5));
		readReg2->SetWireData(instruction.substr(12, 5));
		ALUSrc->SetWireData("0");
		// Jump must be zero because we are branching.
		jump->SetWireData("0");

		writeEnable->SetWireData("0");
		writeReg->SetWireData("00000");
		writeSel->SetWireData("00");
		immi->SetWireData("000000000000");
		immi2->SetWireData("00000000000000000000");
		sign->SetWireData("0");
		ALUdataSel->SetWireData("0");
		flagControl->SetWireData("000");
		memRead->SetWireData("0");
		memWrite->SetWireData("0");
		memSize->SetWireData("00");
		aui->SetWireData("0");

		// BEQ
		if (func3.compare("000") == 0)
		{

			validState = true;
			assemblyInst = "BEQ";

			ALUop->SetWireData("10101");
			flagControl->SetWireData("000");

		}

		// BNE
		if (func3.compare("001") == 0)
		{
			
			validState = true;
			assemblyInst = "BNE";

			ALUop->SetWireData("10110");
			flagControl->SetWireData("001");

		}

		// BLT
		if (func3.compare("100") == 0)
		{

			validState = true;
			assemblyInst = "BLT";

			ALUop->SetWireData("10111");
			flagControl->SetWireData("010");

		}

		// BGE
		if (func3.compare("101") == 0)
		{

			validState = true;
			assemblyInst = "BGE";

			ALUop->SetWireData("11000");
			flagControl->SetWireData("011");

		}

		// BLTU
		if (func3.compare("110") == 0)
		{

			validState = true;
			assemblyInst = "BLTU";

			ALUop->SetWireData("11001");
			flagControl->SetWireData("100");

		}

		// BGEU
		if (func3.compare("111") == 0)
		{

			validState = true;
			assemblyInst = "BGEU";

			ALUop->SetWireData("11010");
			flagControl->SetWireData("101");

		}

	}

	// LUI Operation
	if (opcode.compare("0110111") == 0)
	{

		immi2->SetWireData(instruction.substr(0, 20));
		writeEnable->SetWireData("1");
		writeReg->SetWireData(instruction.substr(20, 5));
		writeSel->SetWireData("10");
		aui->SetWireData("0");

		// Default states.
		readReg1->SetWireData("00000");
		readReg2->SetWireData("00000");
		immi->SetWireData("000000000000");
		ALUSrc->SetWireData("0");
		ALUop->SetWireData("00000");
		ALUdataSel->SetWireData("0");
		flagControl->SetWireData("000");
		offset->SetWireData("0000000000000");
		memRead->SetWireData("0");
		memWrite->SetWireData("0");
		memSize->SetWireData("00");
		jump->SetWireData("0");
        sign->SetWireData("1");

		validState = true;
		assemblyInst = "LUI";

	}

	// AUIPC Operations
	if (opcode.compare("0010111") == 0)
	{

		immi2->SetWireData(instruction.substr(0, 20));
		writeEnable->SetWireData("1");
		writeReg->SetWireData(instruction.substr(20, 5));
		writeSel->SetWireData("10");
		aui->SetWireData("1");

		// Default states.
		readReg1->SetWireData("00000");
		readReg2->SetWireData("00000");
		immi->SetWireData("000000000000");
		ALUSrc->SetWireData("0");
		ALUop->SetWireData("00000");
		ALUdataSel->SetWireData("0");
		flagControl->SetWireData("000");
		offset->SetWireData("0000000000000");
		memRead->SetWireData("0");
		memWrite->SetWireData("0");
		memSize->SetWireData("00");
		jump->SetWireData("0");
        sign->SetWireData("1");

		validState = true;
		assemblyInst = "AUIPC";

	}
	
	// JAL Operations
	if (opcode.compare("1101111") == 0)
	{

		immi2->SetWireData(instruction.substr(0, 1) + instruction.substr(12, 8) + instruction.substr(11, 1) +instruction.substr(1, 10));
		writeEnable->SetWireData("1");
		writeReg->SetWireData(instruction.substr(20, 5));
		writeSel->SetWireData("11");
		jump->SetWireData("1");
		jalr->SetWireData("0");

		// Default states.
		readReg1->SetWireData("00000");
		readReg2->SetWireData("00000");
		immi->SetWireData("000000000000");
		ALUSrc->SetWireData("0");
		ALUop->SetWireData("00000");
		ALUdataSel->SetWireData("0");
		flagControl->SetWireData("000");
		offset->SetWireData("0000000000000");
		memRead->SetWireData("0");
		memWrite->SetWireData("0");
		memSize->SetWireData("00");
        sign->SetWireData("1");

		validState = true;
		assemblyInst = "JAL";

	}

	// JALR Operations
	if (opcode.compare("1100111") == 0)
	{

		immi->SetWireData(instruction.substr(0, 12));
		readReg1->SetWireData(instruction.substr(12, 5));
		writeEnable->SetWireData("1");
		writeReg->SetWireData(instruction.substr(20, 5));
		writeSel->SetWireData("11");
		jump->SetWireData("1");
		jalr->SetWireData("1");
		sign->SetWireData("1");

		// Default states.
		readReg2->SetWireData("00000");
		immi2->SetWireData("00000000000000000000");
		ALUSrc->SetWireData("0");
		ALUop->SetWireData("00000");
		ALUdataSel->SetWireData("0");
		flagControl->SetWireData("000");
		offset->SetWireData("0000000000000");
		memRead->SetWireData("0");
		memWrite->SetWireData("0");
		memSize->SetWireData("00");

		validState = true;
		assemblyInst = "JALR";

	}

}

