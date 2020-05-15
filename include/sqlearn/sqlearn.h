#pragma once

#include <string>
#include <iostream>

#define _GLIBCXX_USE_CXX11_ABI 1
#define PAGE_SIZE 4096

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
	 * Closes the connection to the db and frees allocated memory.
	 */
	void close(void);
}