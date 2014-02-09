#ifndef CONF_H
#define CONF_H

#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

#include "StringUtils.h"

namespace utils
{


    class Conf
    {
        public:

            static char* getConfChar(string tabValue);
            static string getConf(string tabValue);
            static void load();
static void reload();
            static char* CONFIG_FILE ;
            static bool getQuitter();
            static void setQuitter(bool b);
        private:
            static std::map<std::string,std::string> tab;
            static bool* quitter;
    };
}
#endif // CONF_H
