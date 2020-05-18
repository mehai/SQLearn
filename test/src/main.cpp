#include <iostream>
#include <sqlearn/sqlearn.h>

int main(int argc, char** argv)
{
	sqlearn::init();
	
	std::cout << "Running unit tests..." << std::endl;

	std::cout << sqlearn::unit_test(DISK_INTERFACE_TESTS) << std::endl;

	std::cout << sqlearn::unit_test(BUFFER_POOL_ENGINE_TESTS) << std::endl;

	sqlearn::close();
}
