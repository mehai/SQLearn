#pragma once

#include <iostream>
#include <string>
#include <fstream>

namespace sqlearn
{
    class DiskInterface {  
        public:
            DiskInterface(const std::string &db_filename);
            ~DiskInterface();

            /**
		     * Returns the size (in bytes) of the db file.
		     */
            unsigned int get_file_size();

            /**
		     * Writes a page with the given content.
		     * @param p_id id of the page to be written.
		     * @param buffer content to be written.
		     * @return true / false - success / failure
		     */
            bool write_page(int p_id, const char *buffer);

            /**
		     * Reads the given page from file.
		     * @param p_id id of page to be read.
		     * @param buffer content which was read.
		     * @return true / false - success /failure
		     */
            bool read_page(int p_id, char *buffer);
        
        private:
        	/* db file */
            std::string db_filename;
            std::fstream db;
            /* log file */
            std::string log_filename;
            std::fstream log;
            /* other state variables */
            int page;
    };
}