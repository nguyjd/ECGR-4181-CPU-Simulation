#include <iostream>
#include "DataMemory.h"
#include "CPU.h"
#include "BusArbiter.h"

#include <chrono>
#include <thread>

int main()
{

	int clockCount = 0;
	bool delay = false;
	
	// Ram input Wires
	Wire* memSize = new Wire(2);
	Wire* memRead = new Wire(1);
	Wire* memWrite = new Wire(1);
	Wire* dataIn = new Wire(32);
	Wire* address = new Wire(32);

	// Ram output Wires
	Wire* outputEightBits = new Wire(8);
	Wire* outputSixteenBits = new Wire(16);
	Wire* outputThirtyTwoBits = new Wire(32);

	// Control lines
	Wire* requestLine1 = new Wire(1);
	Wire* grantLine1 = new Wire(1);
	Wire* interrupt1 = new Wire(1);
	Wire* requestLine2 = new Wire(1);
	Wire* grantLine2 = new Wire(1);
	Wire* interrupt2 = new Wire(1);
	Wire* requestLine3 = new Wire(1);
	Wire* grantLine3 = new Wire(1);
	Wire* interrupt3 = new Wire(1);
	Wire* requestLine4 = new Wire(1);
	Wire* grantLine4 = new Wire(1);
	Wire* interrupt4 = new Wire(1);
	Wire* halt1 = new Wire(1);
	Wire* halt2 = new Wire(1);
	Wire* halt3 = new Wire(1);
	Wire* halt4 = new Wire(1);

	Wire* bus = new Wire(36);

	CPU* cpu1 = new CPU(bus, requestLine1, grantLine1, interrupt1, halt1, dataIn);
	CPU* cpu2 = new CPU(bus, requestLine2, grantLine2, interrupt2, halt2, dataIn);
	CPU* cpu3 = new CPU(bus, requestLine3, grantLine3, interrupt3, halt3, dataIn);
	CPU* cpu4 = new CPU(bus, requestLine4, grantLine4, interrupt4, halt4, dataIn);
	DataMemory* ram = new DataMemory(memSize, memRead, memWrite, dataIn, address, outputEightBits, outputSixteenBits, outputThirtyTwoBits);
	BusArbiter* busArbiter = new BusArbiter();

	// Connect all the control lines.
	busArbiter->ConnectGrantLines(grantLine1, grantLine2, grantLine3, grantLine4);
	busArbiter->ConnectRequestLines(requestLine1, requestLine2, requestLine3, requestLine4);
	busArbiter->ConnectMemoryLines(bus, memRead, memWrite, dataIn);
	busArbiter->ConnectInterruptLines(interrupt1, interrupt2, interrupt3, interrupt4);

	// Force the ram to output 32 bits.
	memSize->SetWireData("10");


	// Feed the cpus intructions.
	cpu1->Read("00000000000000000000000000000001");
	cpu1->Read("00000000000000101000000011000000");
	cpu1->Read("00000000000000000100000000000000");
	cpu1->Write("00000000000000000100000000000000", "11111111111111111111111111111111");
	cpu1->Write("00000000000000101000000000000000", "11111111111111111111111111111111");
	
	
	cpu2->Read("00000000000000000100000000000000");
	cpu2->Write("00000000000000000000000000000001", "10101010010111101010110101011111");
	cpu2->Read("00000000000000000000011000000000");
	cpu2->Read("00000000000000001110000000000000");

	cpu3->Read("00000000000000001110000000000000");
	cpu3->Read("00000000000000001110000000000000");
	cpu3->Write("00000000000000001110000000000000", "10100101011111111001110000011111");
	cpu3->Read("00000000000000001110000000000000");
	cpu3->Write("00000000000000001110000000000000", "10000101000010010000000000000000");
	cpu3->Read("00000000000000000100000000000000");
	cpu3->Read("00000000000000000100000000000000");

	cpu4->Read("00000000000000101000000000000000");
	cpu4->Write("00000000000000101000000000000000", "10100101001010010101111111110000");

	while (true)
	{

		std::cout << "Clock cycle: " << clockCount << std::endl;

		std::cout << "-------------------CPU 1-------------------" << std::endl;
		cpu1->Update();
		std::cout << "-------------------------------------------" << std::endl;
		
		cpu2->CacheSnoop();
		cpu3->CacheSnoop();
		cpu4->CacheSnoop();
		busArbiter->Update();


		std::cout << "-------------------CPU 2-------------------" << std::endl;
		cpu2->Update();
		std::cout << "-------------------------------------------" << std::endl;

		cpu1->CacheSnoop();
		cpu3->CacheSnoop();
		cpu4->CacheSnoop();
		busArbiter->Update();

		std::cout << "-------------------CPU 3-------------------" << std::endl;
		cpu3->Update();
		std::cout << "-------------------------------------------" << std::endl;

		cpu1->CacheSnoop();
		cpu2->CacheSnoop();
		cpu4->CacheSnoop();
		busArbiter->Update();

		std::cout << "-------------------CPU 4-------------------" << std::endl;
		cpu4->Update();
		std::cout << "-------------------------------------------" << std::endl;

		cpu1->CacheSnoop();
		cpu2->CacheSnoop();
		cpu3->CacheSnoop();
		busArbiter->Update();

		// Split the wire so the ram can use it.
		address->SetWireData(bus->GetWireDataStr().substr(4, -1));
		ram->Update();
		bus->SetWireData(bus->GetWireDataStr().substr(0, 4) + outputThirtyTwoBits->GetWireDataStr());

		// Slowing down the clock.
		if (delay)
		{

			std::this_thread::sleep_for(std::chrono::milliseconds(200));

		}

		if (halt1->GetWireDataStr() == "1" && halt2->GetWireDataStr() == "1" && halt3->GetWireDataStr() == "1" && halt4->GetWireDataStr() == "1")
		{

			break;

		}

		clockCount++;
		std::cout << std::endl;
		std::cout << std::endl;

	}

	
	delete memSize;
	delete memRead;
	delete memWrite;
	delete dataIn;
	delete address;
	delete outputEightBits;
	delete outputSixteenBits;
	delete outputThirtyTwoBits;
	delete requestLine1;
	delete grantLine1;
	delete requestLine2;
	delete grantLine2;
	delete requestLine3;
	delete grantLine3;
	delete requestLine4;
	delete grantLine4;
	delete bus;
	delete cpu1;
	delete cpu2;
	delete cpu3;
	delete cpu4;
	delete ram;
	delete busArbiter;

	return 0;

}