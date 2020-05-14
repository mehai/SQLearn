#pragma once

#include <iostream>
#include <string>

namespace sqlearn
{
    class BufferPoolEngine {  
        public:
            BufferPoolEngine(const unsigned int size);
            ~BufferPoolEngine();
            unsigned int getSize(void);
        
        private:
            unsigned int size;
    };
}