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
        static string MItexte(Files::Fichier file);
        static string MIhtml(Files::Fichier file);
};

#endif // ALGO_H
