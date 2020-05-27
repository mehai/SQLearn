#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include "headers/memory/disk_interface.h"
#include "headers/memory/page.h"
#include "headers/memory/replacer.h"

namespace sqlearn
{
    class BufferPoolEngine {
        friend class Replacer;
        friend class LinearReplacer;
        public:
            BufferPoolEngine(const unsigned int size, const std::string& db_filename);
            BufferPoolEngine(const unsigned int size);
            ~BufferPoolEngine();

            unsigned int get_size(void);
            DiskInterface *get_disk_interface(void);
            char *get_page(unsigned int page_id);

        private:
            void load_page(unsigned int page_id);

            unsigned int size;
            std::unordered_map<unsigned int, unsigned int> page_table;
            Page *buffer;
            Replacer *replacer;
            DiskInterface *disk;
    };
}