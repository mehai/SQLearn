#pragma once

#include <iostream>
#include <string>

#include "headers/memory/buffer_pool_engine.h"
#include "headers/memory/page.h"

namespace sqlearn
{
    class BufferPoolEngine;
    class Replacer {  
        public:
            Replacer (BufferPoolEngine *buffer_pool) : buffer_pool(buffer_pool) {}
            virtual ~Replacer() {}
            virtual unsigned int next_slot() = 0;

        protected:
            BufferPoolEngine *buffer_pool;
    };
}