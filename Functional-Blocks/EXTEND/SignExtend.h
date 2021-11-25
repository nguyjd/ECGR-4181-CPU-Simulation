#ifndef __SIGNEXTEND_H__
#define __SIGNEXTEND_H__

#include "Extend.h"

class SignExtend : public Extend
{

public:

	SignExtend() : Extend() {}
	SignExtend(Wire* input, Wire* output) : Extend(input, output) {};

	void Update();

};


#endif