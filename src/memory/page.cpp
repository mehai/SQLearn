#include "headers/memory/page.h"
#include "headers/config.h"

#include <iostream>
#include <cstring>
#include <cstdlib>

namespace sqlearn
{
    Page::Page()
    {
        id = 0;
        dirty = false;
        content = (char *)malloc(PAGE_SIZE);
    }

    Page::Page(unsigned int id)
    {
        this->id = id;
        dirty = false;
        content = (char *)malloc(PAGE_SIZE);
    }

    Page::~Page()
    {
        if (content != nullptr)
            free(content);
    }

    unsigned int Page::get_id(void)
    {
        return id;
    }

    bool Page::is_dirty(void)
    {
        return dirty;
    }

    char *Page::get_content(void)
    {
        return content;
    }

    void Page::set(unsigned int id, char *content)
    {
        this->id = id;
        this->content = content;
        dirty = false;
    }
}