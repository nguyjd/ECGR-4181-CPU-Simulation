#include <iostream>
#include <Adder.h>


int main()
{
	std::string in1 = "00000000000000000000000000000001";
	std::string in2 = "00000000000000000000000000000101";


	Adder *adda = new Adder(in1, in2);
	std::cout << adda->OutputResult() << std::endl;


	std::cout << "Hello World" << std::endl;

	return 0;

}