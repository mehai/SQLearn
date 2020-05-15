#include "headers/memory/disk_interface.h"

#include <iostream>
#include <string>
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
        return 0;
    }

    bool DiskInterface::write_page(int p_id, const char *buffer)
    {
        return true;
    }

    bool DiskInterface::read_page(int p_id, char *buffer)
    {
        return true;
    }

}