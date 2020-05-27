#include <iostream>
#include <string>
#include <cstring>

#include "headers/memory/buffer_pool_engine.h"
#include "headers/memory/linear_replacer.h"

#include "headers/config.h"

namespace sqlearn
{

    BufferPoolEngine::BufferPoolEngine(const unsigned int size, const std::string& db_filename)
    {
        this->size = size;
        std::cout << db_filename << std::endl;
        this->disk = new DiskInterface(db_filename);

        buffer = new Page[size];
        replacer = new LinearReplacer(this);
    }

    BufferPoolEngine::BufferPoolEngine(const unsigned int size)
    {
        this->size = size;
        std::string db_filename = "test.db";
        std::cout << db_filename << std::endl;
        this->disk = new DiskInterface(db_filename);

        buffer = new Page[size];
        replacer = new LinearReplacer(this);
    }

    BufferPoolEngine::~BufferPoolEngine()
    {
        delete disk;
        delete [] buffer;
        delete replacer;
    }

    unsigned int BufferPoolEngine::get_size()
    {
        return size;
    }

    DiskInterface *BufferPoolEngine::get_disk_interface(void)
    {
        return disk;
    }

    char *BufferPoolEngine::get_page(unsigned int page_id)
    {
        /* page not in buffer */
        if (page_table.find(page_id) == page_table.end()) {
            load_page(page_id);
        }

        unsigned int idx = page_table[page_id];
        return buffer[idx].get_content();
    }

    void BufferPoolEngine::load_page(unsigned int page_id)
    {
        char *page_content = (char *)malloc(PAGE_SIZE);

        if (!disk->read_page(page_id, page_content))
            return;

        /* call replacer to empty a space in the buffer */
        int idx = replacer->next_slot();
        unsigned int former_page_id = buffer[idx].get_id();
        page_table.erase(former_page_id);

        /* add page to the new empty spot and in page_table*/
        buffer[idx].set(page_id, page_content);
        page_table[page_id] = idx;
    }
}