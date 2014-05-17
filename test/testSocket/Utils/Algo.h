#ifndef ALGO_H
#define ALGO_H
#include "StringUtils.h"
#include <string>
#include <sstream>

class Algo
{
    public:
        static string generateMotImportant(Files::Fichier file);
    protected:
    private:
        static string MItexte(string file);
        static string MIhtml(string file);
        static vector<string> important;
};

#endif // ALGO_H
