#ifndef STRINGUTILS_H_INCLUDED
#define STRINGUTILS_H_INCLUDED
#include <string>
#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "../Files/Fichier.h"


using namespace std;

namespace utils
{
    const string RETOURLIGNE = "\r\n";
    class str
    {
        public:
            static vector<string> split(string str, string sep);
            static char* stringToChar(string str);
            static int calculNote(string text,string motImportant);
            static string generateMotImportant(Files::Fichier file);
            static void showFile(string path);
    };
}


#endif // STRINGUTILS_H_INCLUDED
