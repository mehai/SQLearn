#pragma once

#include <string>
#include <iostream>

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