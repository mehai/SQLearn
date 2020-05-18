#include "sqlearn/sqlearn.h"
#include "headers/memory/buffer_pool_engine.h"
#include "headers/tests/tests.h"

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

	std::string unit_test(int unit_code)
	{
		int passed, total;

		init_unit_tests();

		total = number_of_tests(unit_code);
		passed = run_unit_tests(unit_code);

		return "RESULT: " + std::to_string(passed) + " / " + std::to_string(total) + " PASSED FOR " + name_of_test(unit_code);
	}

	void close()
	{
		delete bufferPool;
	}
}