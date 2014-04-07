#include "Algo.h"

using namespace utils;

/**
*@return les mots importants séparé par une virgule
**/
string Algo::generateMotImportant(Files::Fichier file)
{
    if(file.getTypeInt() == F_HTML)
        return MIhtml(file.getTextFull());
    return MItexte(file.getTextFull());
}

string Algo::MIhtml(Files::Fichier file)
{
    vector<string> provisoire = str::split(file.getTextFull()," ");
    vector<string> important = str::split(file.getNom()," ");

    return "lucas, is ,the ,best";
}

string Algo::MItexte(Files::Fichier file)
{
    vector<string> important = str::split(file.getNom()," ");
    vector<string> provisoire = str::split(file.getTextFull()," ");

    for(uint i = 0; i < provisoire.size() ; i++)
    {
        string strToTest = provisoire[i];
        bool testImportant = (strToTest.size() > 3 && str::checkIsAlphabet(strToTest)) //verif basic
                             && (
                                 str::isUpper(provisoire[i])                                //verif important
                                 || str::countOcurence(file.getTextFull(),provisoire[i]) >= 3
                             );

        if(testImportant)
            important.push_back(provisoire[i]);
    }

    provisoire.clear();
    str::removeDuplicate(important);

    ostringstream strToReturn("");
    for(uint i = 0; i < important.size() ; i++)
    {
        strToReturn << important[i];
        if(important.size()-1 != i) //si on est pas le dernier on ajoute une ,
            strToReturn << ",";
    }

    return strToReturn.str();
}

