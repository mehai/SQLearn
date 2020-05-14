#pragma once

#include <string>
#include <iostream>

namespace sqlearn
{
	/**
	 * Initializes necessary infrastructure for query execution
	 */
	void init(void);

	/**
	 * executes given SQL query and returns result.
	 */
	std::string execute(const std::string& query);
}