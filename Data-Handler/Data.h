#ifndef __DATA_H__
#define __DATA_H__

#include <string>
#include <iostream>

class Data
{

public:
	Data();
	Data(std::string data);

	// Set the data.
	void SetData(std::string data);

	// Return instruction as a string
	std::string GetDataStr();
	bool IsDataValid();

protected:

	// Check the data for invalid chars and correct length.
	virtual bool DataValidation();

	// True if the data is 32-bit and only 1 and 0
	bool validData;
	std::string dataStr;
	

};


#endif
