#include "headers/memory/buffer_pool_engine.h"

#include <iostream>
#include <string>

namespace sqlearn
{
    BufferPoolEngine::BufferPoolEngine(const unsigned int size)
    {
        this->size = size;
    }

    BufferPoolEngine::~BufferPoolEngine()
    {
        
    }

    unsigned int BufferPoolEngine::getSize()
    {
        return size;
    }
}