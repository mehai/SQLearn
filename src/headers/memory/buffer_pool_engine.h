#pragma once

#include <iostream>
#include <string>

#include "headers/memory/disk_interface.h"

namespace sqlearn
{
    class BufferPoolEngine {  
        public:
            BufferPoolEngine(const unsigned int size);
            ~BufferPoolEngine();
            unsigned int getSize(void);
            DiskInterface *getDiskInterface(void);
        
        private:
            unsigned int size;
            DiskInterface *disk;
    };
}