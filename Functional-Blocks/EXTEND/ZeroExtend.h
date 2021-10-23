#ifndef __ZEROEXTEND_H__
#define __ZEROEXTEND_H__

#include "Extend.h"

class ZeroExtend : public Extend
{

public:

	ZeroExtend() : Extend() {}
	ZeroExtend(Wire* input, Wire* output) : Extend(input, output) {};

	void Update();

};

#endif