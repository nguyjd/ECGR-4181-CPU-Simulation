#include "BusArbiter.h"

BusArbiter::BusArbiter()
{

	requestLine1 = nullptr;
	requestLine2 = nullptr;
	requestLine3 = nullptr;
	requestLine4 = nullptr;

	grantLine1 = nullptr;
	grantLine2 = nullptr;
	grantLine3 = nullptr;
	grantLine4 = nullptr;

	interrupt1 = nullptr;
	interrupt2 = nullptr;
	interrupt3 = nullptr;
	interrupt4 = nullptr;

	memBus = nullptr;
	memRead = nullptr;
	memWrite = nullptr;
	memData = nullptr;

}

void BusArbiter::Update()
{

	if (memBus->GetWireDataStr() == "000000000000000000000000000000000000")
	{

		memWrite->SetWireData("0");

	}

	if (memBus->GetWireDataStr().substr(0, 2).compare("01") == 0)
	{

		memRead->SetWireData("1");

	}
	else
	{

		memRead->SetWireData("0");

	}

	// Cache 1
	if (requestLine1->GetWireDataStr().compare("1") == 0)
	{

		if ((requestLine2->GetWireDataStr().compare("0") == 0 && requestLine3->GetWireDataStr().compare("0") == 0 && requestLine4->GetWireDataStr().compare("0") == 0))
		{

			grantLine1->SetWireData("1");

		}

	}
	else
	{

		grantLine1->SetWireData("0");

	}

	// Cache 2
	if (requestLine2->GetWireDataStr().compare("1") == 0)
	{

		if (requestLine1->GetWireDataStr().compare("0") == 0 && requestLine3->GetWireDataStr().compare("0") == 0 && requestLine4->GetWireDataStr().compare("0") == 0)
		{

			grantLine2->SetWireData("1");

		}

	}
	else
	{

		grantLine2->SetWireData("0");

	}

	// Cache 3
	if (requestLine3->GetWireDataStr().compare("1") == 0)
	{

		if (requestLine1->GetWireDataStr().compare("0") == 0 && requestLine2->GetWireDataStr().compare("0") == 0 && requestLine4->GetWireDataStr().compare("0") == 0)
		{

			grantLine3->SetWireData("1");

		}

	}
	else
	{

		grantLine3->SetWireData("0");

	}

	// Cache 4
	if (requestLine4->GetWireDataStr().compare("1") == 0)
	{

		if (requestLine1->GetWireDataStr().compare("0") == 0 && requestLine3->GetWireDataStr().compare("0") == 0 && requestLine2->GetWireDataStr().compare("0") == 0)
		{

			grantLine4->SetWireData("1");

		}

	}
	else
	{

		grantLine4->SetWireData("0");

	}

	if (interrupt1->GetWireDataStr().compare("1") == 0 || interrupt2->GetWireDataStr().compare("1") == 0 || interrupt3->GetWireDataStr().compare("1") == 0 || interrupt4->GetWireDataStr().compare("1") == 0)
	{

		//memBus->SetWireData("00" + memBus->GetWireDataStr().substr(2, -1));

		grantLine1->SetWireData("0");
		grantLine2->SetWireData("0");
		grantLine3->SetWireData("0");
		grantLine4->SetWireData("0");

		if (interrupt1->GetWireDataStr().compare("1") == 0)
		{

			grantLine1->SetWireData("1");

		}

		if (interrupt2->GetWireDataStr().compare("1") == 0)
		{

			grantLine2->SetWireData("1");

		}

		if (interrupt3->GetWireDataStr().compare("1") == 0)
		{

			grantLine3->SetWireData("1");

		}

		if (interrupt4->GetWireDataStr().compare("1") == 0)
		{

			grantLine4->SetWireData("1");

		}

		if (memBus->GetWireDataStr().substr(2, 2).compare("10") == 0)
		{

			memWrite->SetWireData("1");

		}
		else
		{

			memWrite->SetWireData("0");

		}

	}
	else
	{

		memWrite->SetWireData("0");

	}

}

void BusArbiter::ConnectRequestLines(Wire* wire1, Wire* wire2, Wire* wire3, Wire* wire4)
{

	requestLine1 = wire1;
	requestLine2 = wire2;
	requestLine3 = wire3;
	requestLine4 = wire4;

}

void BusArbiter::ConnectGrantLines(Wire* wire1, Wire* wire2, Wire* wire3, Wire* wire4)
{

	grantLine1 = wire1;
	grantLine2 = wire2;
	grantLine3 = wire3;
	grantLine4 = wire4;

}

void BusArbiter::ConnectInterruptLines(Wire* wire1, Wire* wire2, Wire* wire3, Wire* wire4)
{

	interrupt1 = wire1;
	interrupt2 = wire2;
	interrupt3 = wire3;
	interrupt4 = wire4;

}

void BusArbiter::ConnectMemoryLines(Wire* bus, Wire* read, Wire* write, Wire* data)
{

	memBus = bus;
	memRead = read;
	memWrite = write;
	memData = data;

}
