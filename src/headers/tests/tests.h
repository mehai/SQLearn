#include <string>
#include <iostream>

#define TOTAL_TEST_SUITES 2

namespace sqlearn
{
    void init_unit_tests(void);

    int number_of_tests(int unit_code);

    int run_unit_tests(int unit_code);

    std::string name_of_test(int unit_code);

    bool test_function();
}