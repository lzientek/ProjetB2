#ifndef STRINGUTILS_H_INCLUDED
#define STRINGUTILS_H_INCLUDED
#define COEF_IMPORTANCE_MOT_IMPORTANT 100
#include "../Files/Fichier.h"
#include <string>
#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>



using namespace std;

namespace utils
{
    const string RETOURLIGNE = "\r\n";
    class str
    {
        public:
            static vector<string> split(string str, string sep);
            static char* stringToChar(string str);
            static int calculNote(vector<string> motsRecherche,string text,string motImportant);
            static string generateMotImportant(Files::Fichier file);
            static void showFile(string path);
            static void supprimerTousLesCharacteres(string &chaine, char c);
            static void replaceAll(std::string& str, const std::string& from, const std::string& to);
            static string validXmlstring(string xml);
            static int countOcurence(string mot, string dans);
            static vector<string> getUrls(string text);
            static void removeDuplicate(vector<string> &tab);
            static void removeFrom(vector<string> &into,vector<string> from);


    };
}


#endif // STRINGUTILS_H_INCLUDED
