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
            bool is_valid(void);
            void set_valid(bool validity);
            void set_dirty(bool dirty);
            char *get_content(void);
            void set(unsigned int id, char *content);

        private:
            unsigned int id;
            bool dirty, valid;
            char *content;
    };
}