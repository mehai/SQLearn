#include "headers/memory/disk_interface.h"
#include "headers/config.h"

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

#define EXT ".db"
#define EXT_LEN 3
#define LOG_FILENAME "sqlearn.log"

namespace sqlearn
{

    DiskInterface::DiskInterface(const std::string &db_filename)
    {
        /* check for the right extension */
        if (db_filename.length() <= EXT_LEN ||
            db_filename.compare(db_filename.length() - EXT_LEN, EXT_LEN, EXT)) {
            std::cerr << "[ERROR] Bad filename format." << std::endl;
            exit(1);
        }

        /* try opening files */
        db.open(db_filename, std::ios::in | std::ios::out | std::ios::binary);
        if (!db.is_open()) {
            /* create new file */
            std::cerr << "[WARN] File doesn't exist. Creating..." << std::endl;
            db.clear();
            db.open(db_filename, std::ios::trunc | std::ios::out | std::ios::binary);
            db.close();
            /* open with original flags */
            db.open(db_filename, std::ios::in | std::ios::out | std::ios::binary);
        }

        log.open(LOG_FILENAME, std::ios::out | std::ios::app);
        if (!log.is_open()) {
            /* create new file */
            std::cerr << "[WARN] File doesn't exist. Creating..," << std::endl;
            log.clear();
            log.open(LOG_FILENAME, std::ios::out | std::ios::trunc);
            log.close();
            /* open with original flags */
            log.open(LOG_FILENAME, std::ios::out | std::ios::app);
        }

        /* assign filenames */
        this->db_filename = db_filename;
        this->log_filename = LOG_FILENAME;
    }

    DiskInterface::~DiskInterface()
    {
        db.close();
        log.close();
    }

    unsigned int DiskInterface::get_file_size()
    {
        std::streampos begin, end;
        db.seekg(0, std::ios::beg);
        begin = db.tellg();
        db.seekg(0, std::ios::end);
        end = db.tellg();
        return (unsigned int)(end - begin);
    }

    bool DiskInterface::write_page(unsigned int p_id, const char *buffer)
    {
        unsigned int total_pages;
        char *tmp;

        total_pages = get_file_size();
        total_pages /= PAGE_SIZE;

        /* fill the empty space if it is the case */
        if (total_pages < p_id) {
            int new_empty_pages = p_id - total_pages;
            tmp = new char[new_empty_pages * PAGE_SIZE];
            memset(tmp, 0, new_empty_pages * PAGE_SIZE);
            db.seekp(0, std::ios::end);
            db.write(tmp, new_empty_pages * PAGE_SIZE);
            if (db.bad()) {
                std::cerr << "[ERROR] Could not write to file." << std::endl;
                return false;
            }
        }

        /* write the new page */
        db.seekp(p_id * PAGE_SIZE, std::ios::beg);
        db.write(buffer, PAGE_SIZE);
        if (db.bad()) {
            std::cerr << "[ERROR] Could not write to file." << std::endl;
            return false;
        }
        db.flush();

        return true;
    }

    bool DiskInterface::read_page(unsigned int p_id, char *buffer)
    {
        unsigned int file_size;
        char *tmp;

        file_size = get_file_size();
        if (p_id * PAGE_SIZE >= file_size) {
            std::cerr << "[ERROR] Inexistent page." << std::endl;
            return false;
        }

        db.seekg(p_id * PAGE_SIZE, std::ios::beg);
        db.read(buffer, PAGE_SIZE);
        if (db.bad()) {
            std::cerr << "[ERROR] Could not read from file." << std::endl;
            return false;
        }

        return true;
    }

}