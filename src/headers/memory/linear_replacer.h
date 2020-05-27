#pragma once

#include <iostream>
#include <string>

#include "headers/memory/buffer_pool_engine.h"
#include "headers/memory/page.h"
#include "headers/memory/replacer.h"

namespace sqlearn
{
    class LinearReplacer: public Replacer {  
        public:
            LinearReplacer(BufferPoolEngine *buffer_pool) : Replacer(buffer_pool) {}
            ~LinearReplacer() {}

            /**
             * Finds the next empty slot in the buffer and returns its index.
             */
            unsigned int next_slot();
    };
}