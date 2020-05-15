#include "sqlearn/sqlearn.h"
#include "headers/memory/buffer_pool_engine.h"

#include <iostream>

namespace sqlearn
{

	static BufferPoolEngine *bufferPool;

	void init()
	{
		bufferPool = new BufferPoolEngine (10);
	}

	std::string execute(const std::string& query)
	{
		if (query == "BUFFER TEST") {
			std::cout << "buffer size: " << bufferPool->getSize() << std::endl;
		}
		return "Done";
	}

	void close()
	{
		delete bufferPool;
	}
}