#include "StringUtils.h"


vector<string> utils::str::split(string str, string sep)
{
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    vector<std::string> arr;
    current=strtok(cstr,sep.c_str());

    while(current != NULL)
    {
        arr.push_back(current);
        current=strtok(NULL, sep.c_str());
    }

    return arr;
}


char* utils::str::stringToChar(string str)
{
    char* cstr=const_cast<char*>(str.c_str());
    return cstr;
}


int utils::str::calculNote(string text,string motImportant)
{
    return 2;//TODO: implémenter calcul note
}


/**
*@return les mots importants séparé par une virgule
**/
string utils::str::generateMotImportant(string fullText)
{
    //TODO: écrire cette fonction de taré
    return "lucas,zientek";
}
