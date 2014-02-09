#ifndef STATS_H
#define STATS_H
#include "Conf.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <ctime>

namespace utils
{


    class Stats
    {
        public:

            static void load();
            static void save();
            static void save(std::string fileName);
            static int getNbRequeteServ();
            static void incRequeteServ(int act,string key = "");
        private:
            static int nbRequeteServeur;
            static bool* quitter;
            static std::string actualAction;
    };
}
#endif // STATS_H
