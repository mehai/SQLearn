#pragma once

#include <string>
#include <iostream>

#define DISK_INTERFACE_TESTS 0
#define BUFFER_POOL_ENGINE_TESTS 1

namespace sqlearn
{
	/**
	 * Initializes necessary infrastructure for query execution.
	 */
	void init(void);

	/**
	 * Executes given SQL query and returns result.
	 */
	std::string execute(const std::string& query);

	/**
	 * Unit tests.
	 * @param unit_code code of the unit to be tested 
	 */
	std::string unit_test(int unit_code);

	/**
	 * Closes the connection to the db and frees allocated memory.
	 */
	void close(void);
}