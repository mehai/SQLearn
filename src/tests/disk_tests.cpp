#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cassert>

#include "headers/tests/disk_tests.h"
#include "headers/tests/test_utils.h"
#include "headers/memory/disk_interface.h"


namespace sqlearn
{
    bool disk_test_1()
    {
        DiskInterface disk("disk_test_1.db");

        /* check file size */
        if (disk.get_file_size() != 0)
            return false;
        
        /* write page 0 */
        char page[PAGE_SIZE];
        fill_random(page, PAGE_SIZE);
        if (!disk.write_page(0, page))
            return false;
        
        /* read page 0 */
        char result[PAGE_SIZE];
        if (!disk.read_page(0, result))
            return false;
        
        /* check if buffers are equal */
        if (std::memcmp(page, result, PAGE_SIZE))
            return false;

        /* cleanup */
        std::remove("disk_test_1.db");

        return true;
    }

    bool disk_test_2()
    {
        DiskInterface disk("disk_test_2.db");

        /* check file size */
        if (disk.get_file_size() != 0)
            return false;
        
        /* write first 3 pages */
        const int num_pages = 3;
        char page[PAGE_SIZE  * num_pages];
        fill_random(page, PAGE_SIZE * num_pages);

        for (int i = 0; i < num_pages; i++)
            if (!disk.write_page(i, page + PAGE_SIZE * i))
                return false;
        
        /* check file size after write */
        if (disk.get_file_size() != PAGE_SIZE * num_pages)
            return false;

        /* read first 3 pages */
        char result[PAGE_SIZE * num_pages];
        for (int i = 0; i < num_pages; i++)
            if (!disk.read_page(i, result + PAGE_SIZE * i))
                return false;
        
        /* check file size after read */
        if (disk.get_file_size() != PAGE_SIZE * num_pages)
            return false;

        /* check if buffers are equal */
        if (std::memcmp(page, result, PAGE_SIZE * num_pages))
            return false;

        /* cleanup */
        std::remove("disk_test_2.db");

        return true;
    }
}