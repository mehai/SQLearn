#include <iostream>
#include <sqlearn/sqlearn.h>

int main(int argc, char** argv)
{
	sqlearn::init();
	
	std::cout << sqlearn::execute("BUFFER TEST") << std::endl;
}
