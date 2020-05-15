#include "headers/memory/buffer_pool_engine.h"

#include <iostream>
#include <string>

namespace sqlearn
{
    BufferPoolEngine::BufferPoolEngine(const unsigned int size)
    {
        this->size = size;
        std::string db_filename = "test.db";
        std::cout << db_filename << std::endl;
        this->disk = new DiskInterface(db_filename);
    }

    BufferPoolEngine::~BufferPoolEngine()
    {
        delete disk;
    }

    unsigned int BufferPoolEngine::getSize()
    {
        return size;
    }
}