#include <iostream>
#include "LevelOneCache.h"

int main()
{

	Wire* memread = new Wire(1);
	Wire* memwrite = new Wire(1);
	Wire* bus = new Wire(36);
	Wire* address = new Wire(32);

	memread->SetWireData("1");

	LevelOneCache* cache = new LevelOneCache(address, memread, memwrite, bus);

	cache->Update();
	address->SetWireData("00000000000000000000000000100001");
	cache->Update();

	delete memread;
	delete memwrite;
	delete bus;
	delete address;
	delete cache;

	return 0;

}