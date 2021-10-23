#include "Wire.h"

Wire::Wire() : Data()
{

	numWire = 0;

}

Wire::Wire(std::string data) : Data(data)
{

	numWire = data.length();
	validData = DataValidation();

}

Wire::Wire(std::string data, long long int wireCount) : Data(data)
{

	numWire = wireCount;
	validData = DataValidation();

}

void Wire::SetWireData(std::string data)
{

	dataStr = data;
	validData = DataValidation();

}

void Wire::ResizeAmountofWires(long long int count)
{

	numWire = count;

}

std::string Wire::GetWireDataStr()
{
	
	return dataStr;

}

long long int Wire::GetAmountofWires()
{

	return numWire;

}

bool Wire::IsWireDataValid()
{
	
	return validData;

}

bool Wire::DataValidation()
{

	// Data Validation
	// Test to see if the data and the number of wire is the same.
	if (dataStr.length() != numWire)
	{

		return false;

	}

	// Test to see if there is any invalid chars
	for (int i = 0; i < dataStr.length(); i++)
	{

		if (dataStr[i] != '0' && dataStr[i] != '1')
		{

			return false;

		}

	}

	return true;

}
