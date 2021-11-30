#include "LevelOneCache.h"

LevelOneCache::LevelOneCache()
{

	
	tagData = new Wire(TAGDATASIZE);
	indexData = new Wire(INDEXDATASIZE);
	offsetData = new Wire(OFFSETDATASIZE);

	for (int i = 0; i < BLOCKCOUNT; i++)
	{

		setOneTags.push_back(new Wire(1 + TAGDATASIZE));
		setTwoTags.push_back(new Wire(1 + TAGDATASIZE));

		setOne.push_back(new Wire(MEMDATASIZE));
		setTwo.push_back(new Wire(MEMDATASIZE));

	}

}

LevelOneCache::~LevelOneCache()
{

	delete tagData;
	delete indexData;
	delete offsetData;

	for (int i = 0; i < BLOCKCOUNT; i++)
	{

		setOneTags.at(i);
		setTwoTags.at(i);

		setOne.at(i);
		setTwo.at(i);

	}

}
