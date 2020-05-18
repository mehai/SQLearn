#include <vector>
#include <array>
#include <string>

#include "headers/tests/tests.h"
#include "headers/tests/disk_tests.h"
#include "headers/tests/buffer_tests.h"


namespace sqlearn
{
    /* state */
    bool initialized = false;

    /* containers */
    std::array<std::vector<bool (*)()>, TOTAL_TEST_SUITES> suite;
    std::array<std::string, TOTAL_TEST_SUITES> suite_names = {
        "DISK INTERFACE TESTS",
        "BUFFER POOL ENGINE TESTS"
    };

    void init_unit_tests()
    {
        if (initialized)
            return;

        /* DISK INTERFACE TESTS */
        suite[0].push_back(&disk_test_1);
        suite[0].push_back(&disk_test_2);

        /* BUFFER POOL ENGINE TESTS */
        suite[1].push_back(&buffer_test_1);
        suite[2].push_back(&buffer_test_2);

        initialized = true;
    }

    int number_of_tests(int unit_code)
    {
        return suite[unit_code].size();
    }

    int run_unit_tests(int unit_code)
    {
        int passed = 0;
        int i = 1;
        for (auto func = suite[unit_code].cbegin(); func != suite[unit_code].cend(); ++func, ++i) 
            if ((*func)())
                passed++;
            else
                std::cerr << "[" << name_of_test(unit_code) << "] Test " << i << " failed." << std::endl;

        return passed;
    }

    std::string name_of_test(int unit_code)
    {
        return suite_names[unit_code];
    }

    bool test_function()
    {
        return true;
    }
}