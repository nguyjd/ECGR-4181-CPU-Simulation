#include "Data.h"

Data::Data()
{

	validData = false;
	dataStr = "";

}

Data::Data(std::string data)
{
	
	dataStr = data;
	validData = DataValidation();

}

void Data::SetData(std::string data)
{

	dataStr = data;
	validData = DataValidation();

}

std::string Data::GetDataStr()
{

	return dataStr;

}

bool Data::IsDataValid()
{

	return validData;

}

bool Data::DataValidation()
{

	// Data Validation
	// Test to see if the data is 32-bits
	if (dataStr.length() != 32)
	{

		return false;

	}

	// Test to see if there is any invalid chars
	for (int i = 0; i < 32; i++)
	{

		if (dataStr[i] != '0' && dataStr[i] != '1')
		{

			return false;

		}

	}

	return true;

}
