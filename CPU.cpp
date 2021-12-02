#include "CPU.h"

CPU::CPU(Wire* memBus, Wire* request, Wire* grant)
{

	memread = new Wire(1);
	memwrite = new Wire(1);
	memAddress = new Wire(32);
	data = new Wire(32);
	stall = new Wire(1);

	cache = new LevelOneCache(memAddress, memread, memwrite, data, stall, request, grant, memBus);

	PC = 0;

}

CPU::~CPU()
{

	delete memread;
	delete memwrite;
	delete memAddress;
	delete cache;
	delete data;
	delete stall;

}

void CPU::Update()
{

	if (stall->GetWireDataStr().compare("1") == 0)
	{

		std::cout << "CPU: CPU is stalled." << std::endl;
		cache->Update();

	}
	else if (PC >= instr.size())
	{

		std::cout << "CPU: There are no more instuctions to run for this CPU. It is in a halted state." << std::endl;
		cache->Update();

	}
	else
	{

		std::cout << "CPU: Running next instruction." << std::endl;

		memAddress->SetWireData(addresses[PC]);

		if (instr[PC].compare("read") == 0)
		{

			memread->SetWireData("1");
			memwrite->SetWireData("0");
			cache->Update();
			memread->SetWireData("0");

		}
		else
		{

			memread->SetWireData("0");
			memwrite->SetWireData("1");
			cache->Update();
			memwrite->SetWireData("0");

		}

		PC++;

	}

	

}

void CPU::CacheSnoop()
{

	cache->Snoop();

}

void CPU::Read(std::string address)
{

	instr.push_back("read");
	addresses.push_back(address);
	instructionData.push_back("00000000000000000000000000000000");

}

void CPU::Write(std::string address, std::string data)
{

	instr.push_back("write");
	addresses.push_back(address);
	instructionData.push_back(data);

}
