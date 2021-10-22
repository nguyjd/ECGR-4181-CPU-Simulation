#include "Decoder.h"

Decoder::Decoder()
{

	validState = false;
	
    // Default Values
	readReg1 = "00000";
	readReg2 = "00000";
	writeEnable = false;
	writeReg = "00000";
	writeSel = "00";
	immi = "000000000000";
	immi2 = "00000000000000000000";
	ALUSrc = false;
	sign = false;
	ALUop = "00000";
	ALUdataSel = false;
	flagControl = "000";
	offset = "0000000000000";
	memRead = false;
	memWrite = false;
	memSize = "00";
	jump = false;
	aui = false;


}

Decoder::Decoder(Instruction inst)
{

	validState = false;
	
    // Default Values
	readReg1 = "00000";
	readReg2 = "00000";
	writeEnable = false;
	writeReg = "00000";
	writeSel = "00";
	immi = "000000000000";
	immi2 = "00000000000000000000";
	ALUSrc = false;
	sign = false;
	ALUop = "00000";
	ALUdataSel = false;
	flagControl = "000";
	offset = "0000000000000";
	memRead = false;
	memWrite = false;
	memSize = "00";
	jump = false;
	aui = false;

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
	std::cout << "readReg1: " << readReg1 << std::endl;
	std::cout << "readReg2: " << readReg2 << std::endl;
	std::cout << "writeEnable: " << writeEnable << std::endl;
	std::cout << "writeReg: " << writeReg << std::endl;
	std::cout << "writeSel: " << writeSel << std::endl;
	std::cout << "immi: " << immi << std::endl;
	std::cout << "immi2: " << immi2 << std::endl;
	std::cout << "ALUSrc: " << ALUSrc << std::endl;
	std::cout << "sign: " << sign << std::endl;
	std::cout << "ALUop: " << ALUop << std::endl;
	std::cout << "ALUdataSel: " << ALUdataSel << std::endl;
	std::cout << "flagControl: " << flagControl << std::endl;
	std::cout << "offset: " << offset << std::endl;
	std::cout << "memRead: " << memRead << std::endl;
	std::cout << "memWrite: " << memWrite << std::endl;
	std::cout << "memSize: " << memSize << std::endl;
	std::cout << "jump: " << jump << std::endl;
	std::cout << "aui: " << aui << std::endl;
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
		
		readReg1 = instruction.substr(7, 5);
		readReg2 = instruction.substr(12, 5);
		writeEnable = true;
		writeReg = instruction.substr(20, 5);
		ALUdataSel = false;
		ALUSrc = false;
		writeSel = "00";

		// Default states.
		immi = "000000000000";
		immi2 = "00000000000000000000";
		flagControl = "000";
		offset = "0000000000000";
		memRead = false;
		memWrite = false;
		memSize = "00";
		jump = false;
		aui = false;
		sign = true;

		// ADD
		if (func7.compare("0000000") == 0 && func3.compare("000") == 0)
		{

			validState = true;
			assemblyInst = "ADD";
			ALUop = "00000";

		}

		// SUB
		if (func7.compare("0100000") == 0 && func3.compare("000") == 0)
		{

			validState = true;
			assemblyInst = "SUB";
			ALUop = "00001";

		}

		// SLL
		if (func7.compare("0000000") == 0 && func3.compare("001") == 0)
		{

			validState = true;
			assemblyInst = "SLL";
			ALUop = "00010";

		}

		// SLT
		if (func7.compare("0000000") == 0 && func3.compare("010") == 0)
		{

			validState = true;
			assemblyInst = "SLT";
			ALUop = "00011";

		}

		// SLTU
		if (func7.compare("0000000") == 0 && func3.compare("011") == 0)
		{

			validState = true;
			assemblyInst = "SLTU";
			ALUop = "00011";

		}

		// XOR
		if (func7.compare("0000000") == 0 && func3.compare("100") == 0)
		{

			validState = true;
			assemblyInst = "XOR";
			ALUop = "00100";

		}

		// SRL
		if (func7.compare("0000000") == 0 && func3.compare("101") == 0)
		{

			validState = true;
			assemblyInst = "SRL";
			ALUop = "00101";

		}

		// SRA
		if (func7.compare("0100000") == 0 && func3.compare("101") == 0)
		{

			validState = true;
			assemblyInst = "SRA";
			ALUop = "00110";

		}

		// OR
		if (func7.compare("0000000") == 0 && func3.compare("110") == 0)
		{

			validState = true;
			assemblyInst = "OR";
			ALUop = "00111";

		}

		// AND
		if (func7.compare("0000000") == 0 && func3.compare("111") == 0)
		{

			validState = true;
			assemblyInst = "AND";
			ALUop = "01000";

		}

		// MUL
		if (func7.compare("0000001") == 0 && func3.compare("000") == 0)
		{

			validState = true;
			assemblyInst = "MUL";
			ALUop = "10000";

		}

		// MULH
		if (func7.compare("0000001") == 0 && func3.compare("001") == 0)
		{

			validState = true;
			assemblyInst = "MULH";
			ALUop = "10001";

		}

		// MULHSU
		if (func7.compare("0000001") == 0 && func3.compare("010") == 0)
		{

			validState = true;
			assemblyInst = "MULHSU";
			ALUop = "10010";

		}

		// MULHU
		if (func7.compare("0000001") == 0 && func3.compare("011") == 0)
		{

			validState = true;
			assemblyInst = "MULHU";
			ALUop = "10011";

		}

		// DIV
		if (func7.compare("0000001") == 0 && func3.compare("100") == 0)
		{

			validState = true;
			assemblyInst = "DIV";
			ALUop = "10100";

		}

		// DIVU
		if (func7.compare("0000001") == 0 && func3.compare("101") == 0)
		{

			validState = true;
			assemblyInst = "DIVU";
			ALUop = "11100";

		}

		// REM
		if (func7.compare("0000001") == 0 && func3.compare("110") == 0)
		{

			validState = true;
			assemblyInst = "REM";
			ALUop = "11101";

		}

		// REMU
		if (func7.compare("0000001") == 0 && func3.compare("111") == 0)
		{

			validState = true;
			assemblyInst = "REMU";
			ALUop = "11110";

		}

	}

	// ALU Immediate Operations
	if (opcode.compare("0010011") == 0)
	{

        // Only used for SLLI SRLI SRAI
		std::string func7 = instruction.substr(0, 7);
		std::string func3 = instruction.substr(17, 3);

		immi = instruction.substr(0, 12);
		readReg1 = instruction.substr(12, 5);
		writeEnable = true;
		writeReg = instruction.substr(20, 5);
		ALUSrc = true;
		ALUdataSel = false;
		writeSel = "00";

		// Default states.
		readReg2 = "00000";
		immi2 = "00000000000000000000";
		flagControl = "000";
		offset = "0000000000000";
		memRead = false;
		memWrite = false;
		memSize = "00";
		jump = false;
		aui = false;

		// ADDI
		if ( func3.compare("000") == 0)
		{

			validState = true;
			assemblyInst = "ADDI";
			sign = true;
			ALUop = "00000";

		}

		// SLTI
		if (func3.compare("010") == 0)
		{

			validState = true;
			assemblyInst = "SLTI";
			sign = true;
			ALUop = "00011";

		}

		// SLTIU
		if (func3.compare("011") == 0)
		{

			validState = true;
			assemblyInst = "SLTIU";
			sign = false;
			ALUop = "01011";

		}

		// XORI
		if (func3.compare("100") == 0)
		{

			validState = true;
			assemblyInst = "XORI";
			sign = true;
			ALUop = "00100";

		}

		// ORI
		if (func3.compare("110") == 0)
		{

			validState = true;
			assemblyInst = "ORI";
			sign = true;
			ALUop = "00111";

		}

		// ANDI
		if (func3.compare("111") == 0)
		{

			validState = true;
			assemblyInst = "ANDI";
			sign = true;
			ALUop = "01000";

		}

        // SLLI
		if (func7.compare("0000000") == 0 && func3.compare("001") == 0)
		{

			validState = true;
			assemblyInst = "SLLI";

			sign = true;
			ALUop = "01001";

		}

        // SRLI
		if (func7.compare("0000000") == 0 && func3.compare("101") == 0)
		{

			validState = true;
			assemblyInst = "SRLI";

			sign = true;
			ALUop = "01010";

		}

        // SRAI
		if (func7.compare("0100000") == 0 && func3.compare("101") == 0)
		{

			validState = true;
			assemblyInst = "SRAI";

			sign = true;
			ALUop = "01100";

		}

	}

	// Load Operations
	if (opcode.compare("0000011") == 0)
	{ 

		std::string func3 = instruction.substr(17, 3);

		writeSel = "01";
		writeEnable = true;
		immi = instruction.substr(0, 12);
		readReg1 = instruction.substr(12, 5);
		writeReg = instruction.substr(20, 5);
		ALUSrc = true;
		ALUdataSel = true;
		memRead = true;
		memRead = false;

		// Default states.
		readReg2 = "00000";
		immi2 = "00000000000000000000";
		flagControl = "000";
		offset = "0000000000000";
		jump = false;
		aui = false;

		// LB
		if (func3.compare("000") == 0)
		{

			validState = true;
			assemblyInst = "LB";

			ALUop = "01111";
			memSize = "00";
			sign = true;

		}

		// LH
		if (func3.compare("001") == 0)
		{

			validState = true;
			assemblyInst = "LH";

			ALUop = "01111";
			memSize = "01";
			sign = true;

		}

		// LW
		if (func3.compare("010") == 0)
		{

			validState = true;
			assemblyInst = "LW";

			ALUop = "01111";
			memSize = "10";
			sign = true;

		}

		// LBU
		if (func3.compare("100") == 0)
		{

			validState = true;
			assemblyInst = "LBU";

			ALUop = "01111";
			memSize = "00";
			sign = false;

		}

		// LHU
		if (func3.compare("101") == 0)
		{

			validState = true;
			assemblyInst = "LHU";

			ALUop = "01111";
			memSize = "01";
			sign = false;

		}

		// LWU
		if (func3.compare("110") == 0)
		{

			validState = true;
			assemblyInst = "LWU";

			ALUop = "01111";
			memSize = "10";
			sign = false;

		}

	}

	// Store Operations
	if (opcode.compare("0100011") == 0)
	{

		std::string func3 = instruction.substr(17, 3);

		immi = instruction.substr(0, 7) + instruction.substr(20, 5);
		readReg1 = instruction.substr(7, 5);
		readReg2 = instruction.substr(12, 5);
		ALUSrc = true;
		ALUdataSel = true;
		sign = true;
		memRead = false;
		memWrite = true;

		// Default states.
		writeEnable = false;
		writeReg = "00000";
		writeSel = "00";
		immi2 = "00000000000000000000";
		jump = false;
		aui = false;
		flagControl = "000";
		offset = "0000000000000";

		// SB
		if (func3.compare("000") == 0)
		{

			validState = true;
			assemblyInst = "SB";

			ALUop = "11011";
            memSize = "00";

		}

		// SH
		if (func3.compare("001") == 0)
		{

			validState = true;
			assemblyInst = "SH";

			ALUop = "11011";
            memSize = "01";

		}

		// SW
		if (func3.compare("010") == 0)
		{

			validState = true;
			assemblyInst = "SW";

			ALUop = "11011";
            memSize = "01";

		}

	}

	// Branch Operations
	if (opcode.compare("1100011") == 0)
	{

		std::string func3 = instruction.substr(17, 3);
		offset = instruction.substr(0, 1) + instruction.substr(24, 1) + instruction.substr(1, 6) + instruction.substr(20, 4) + "0";
		readReg1 = instruction.substr(7, 5);
		readReg2 = instruction.substr(12, 5);
		ALUSrc = false;
		// Jump must be zero because we are branching.
		jump = false;

		writeEnable = false;
		writeReg = "00000";
		writeSel = "00";
		immi = "000000000000";
		immi2 = "00000000000000000000";
		sign = false;
		ALUdataSel = false;
		flagControl = "000";
		memRead = false;
		memWrite = false;
		memSize = "00";
		aui = false;

		// BEQ
		if (func3.compare("000") == 0)
		{

			validState = true;
			assemblyInst = "BEQ";

			ALUop = "10101";
			flagControl = "000";

		}

		// BNE
		if (func3.compare("001") == 0)
		{
			
			validState = true;
			assemblyInst = "BNE";

			ALUop = "10110";
			flagControl = "001";

		}

		// BLT
		if (func3.compare("100") == 0)
		{

			validState = true;
			assemblyInst = "BLT";

			ALUop = "10111";
			flagControl = "010";

		}

		// BGE
		if (func3.compare("101") == 0)
		{

			validState = true;
			assemblyInst = "BGE";

			ALUop = "11000";
			flagControl = "011";

		}

		// BLTU
		if (func3.compare("110") == 0)
		{

			validState = true;
			assemblyInst = "BLTU";

			ALUop = "11001";
			flagControl = "100";

		}

		// BGEU
		if (func3.compare("111") == 0)
		{

			validState = true;
			assemblyInst = "BGEU";

			ALUop = "11010";
			flagControl = "101";

		}

	}

	// LUI Operation
	if (opcode.compare("0110111") == 0)
	{

		immi2 = instruction.substr(0, 20);
		writeEnable = true;
		writeReg = instruction.substr(20, 5);
		writeSel = "10";
		aui = false;

		// Default states.
		readReg1 = "00000";
		readReg2 = "00000";
		immi = "000000000000";
		ALUSrc = false;
		ALUop = "00000";
		ALUdataSel = false;
		flagControl = "000";
		offset = "0000000000000";
		memRead = false;
		memWrite = false;
		memSize = "00";
		jump = false;
        sign = true;

		validState = true;
		assemblyInst = "LUI";

	}

	// AUIPC Operations
	if (opcode.compare("0010111") == 0)
	{

		immi2 = instruction.substr(0, 20);
		writeEnable = true;
		writeReg = instruction.substr(20, 5);
		writeSel = "10";
		aui = true;

		// Default states.
		readReg1 = "00000";
		readReg2 = "00000";
		immi = "000000000000";
		ALUSrc = false;
		ALUop = "00000";
		ALUdataSel = false;
		flagControl = "000";
		offset = "0000000000000";
		memRead = false;
		memWrite = false;
		memSize = "00";
		jump = false;
        sign = true;

		validState = true;
		assemblyInst = "AUIPC";

	}
	
	// JAL Operations
	if (opcode.compare("1101111") == 0)
	{

		immi2 = instruction.substr(0, 1) + instruction.substr(12, 8) + instruction.substr(11, 1) +instruction.substr(1, 10);
		writeEnable = true;
		writeReg = instruction.substr(20, 5);
		writeSel = "11";
		jump = true;
		jalr = false;

		// Default states.
		readReg1 = "00000";
		readReg2 = "00000";
		immi = "000000000000";
		ALUSrc = false;
		ALUop = "00000";
		ALUdataSel = false;
		flagControl = "000";
		offset = "0000000000000";
		memRead = false;
		memWrite = false;
		memSize = "00";
        sign = true;

		validState = true;
		assemblyInst = "JAL";

	}

	// JALR Operations
	if (opcode.compare("1100111") == 0)
	{

		immi = instruction.substr(0, 12);
		readReg1 = instruction.substr(12, 5);
		writeEnable = true;
		writeReg = instruction.substr(20, 5);
		writeSel = "11";
		jump = true;
		jalr = true;
		sign = true;

		// Default states.
		readReg2 = "00000";
		immi2 = "00000000000000000000";
		ALUSrc = false;
		ALUop = "00000";
		ALUdataSel = false;
		flagControl = "000";
		offset = "0000000000000";
		memRead = false;
		memWrite = false;
		memSize = "00";

		validState = true;
		assemblyInst = "JALR";

	}

}


