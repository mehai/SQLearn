#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "headers/memory/buffer_pool_engine.h"
#include "headers/memory/page.h"
#include "headers/memory/linear_replacer.h"
#include "headers/memory/replacer.h"

namespace sqlearn
{
    unsigned int LinearReplacer::next_slot()
    {
        int not_dirty = -1;

        /* search for the first empty slot */
        for (unsigned int i = 0; i != buffer_pool->get_size(); ++i) {
            if (!buffer_pool->buffer[i].is_valid())
                return i;
            if (!buffer_pool->buffer[i].is_dirty())
                not_dirty = i;
        }

        /* no empty slot found, return the last not dirty slot found */
        if (not_dirty != -1)
            return not_dirty;
        
        /* all are dirty pages so flush a random one and return it */
        srand((unsigned int) time(NULL));
        unsigned int rand_idx = rand() % buffer_pool->get_size();

        DiskInterface *disk = buffer_pool->get_disk_interface();
        disk->write_page(rand_idx, const_cast<char *> (buffer_pool->buffer[rand_idx].get_content()));
        buffer_pool->buffer[rand_idx].set_dirty(false);

        return rand_idx;
    }
}