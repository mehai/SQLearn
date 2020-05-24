#pragma once

#include <iostream>
#include <string>

namespace sqlearn
{
    class Page {  
        public:
            Page();
            Page(unsigned int id);
            ~Page();

            unsigned int get_id(void);
            bool is_dirty(void);
            char *get_content(void);
            void set(unsigned int id, char *content);

        private:
            unsigned int id;
            bool dirty;
            char *content;
    };
}