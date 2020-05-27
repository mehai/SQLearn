#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

#include "headers/config.h"
#include "headers/tests/test_utils.h"
#include "headers/memory/buffer_pool_engine.h"
#include "headers/tests/buffer_tests.h"

namespace sqlearn
{
    bool buffer_test_1()
    {
        BufferPoolEngine buffer_pool(10, "buffer_test_1.db");
        DiskInterface *disk = buffer_pool.get_disk_interface();

        /* check file size */
        if (disk->get_file_size() != 0)
            return false;
        
        /* write page 0 */
        char page[PAGE_SIZE];
        fill_random(page, PAGE_SIZE);
        if (!disk->write_page(0, page))
            return false;
        
        /* get page 0 */
        char *result = buffer_pool.get_page(0);
        
        /* check if buffers are equal */
        if (std::memcmp(page, result, PAGE_SIZE))
            return false;

        /* cleanup */
        std::remove("buffer_test_1.db");

        return true;
    }

    bool buffer_test_2()
    {
        BufferPoolEngine buffer_pool(2, "buffer_test_2.db");
        DiskInterface *disk = buffer_pool.get_disk_interface();

        /* check file size */
        if (disk->get_file_size() != 0)
            return false;
        
        /* write first 3 pages */
        const int num_pages = 3;
        char page[PAGE_SIZE  * num_pages];
        fill_random(page, PAGE_SIZE * num_pages);

        for (int i = 0; i < num_pages; i++)
            if (!disk->write_page(i, page + PAGE_SIZE * i))
                return false;
        
        /* check file size after write */
        if (disk->get_file_size() != PAGE_SIZE * num_pages)
            return false;

        /* get all 3 pages */
        char **result = (char **) malloc(num_pages * sizeof(char *));
        for (int i = 0; i < num_pages; i++)
            result[i] = buffer_pool.get_page(i);
        
        /* check file size after read */
        if (disk->get_file_size() != PAGE_SIZE * num_pages)
            return false;

        /* check if buffers are equal */
        for (int i = 0; i < num_pages; i++)
            if (std::memcmp(page + i * PAGE_SIZE, result[i], PAGE_SIZE))
                return false;

        /* cleanup */
        free(result);
        std::remove("buffer_test_2.db");

        return true;
    }
}