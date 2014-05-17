#include "Algo.h"

using namespace utils;

vector<string> Algo::important;
/**
*@return les mots importants séparé par une virgule
**/
string Algo::generateMotImportant(Files::Fichier file)
{
    important = vector<string>();
    if(file.getTypeInt() == F_HTML)
        return MIhtml(file.getTextFull());
    return MItexte(file.getTextFull());
}

string Algo::MIhtml(string file)
{

    file  = utils::str::regex_replace ("<[^>]*>",file,"");
    //    std::regex_replace (file,e," ");
    return MItexte(file);

}

string Algo::MItexte(string file)
{
    file  = utils::str::regex_replace ("[^a-ùA-Z ]",file," ");

    vector<string> provisoire = str::split(file," ");

    for(uint i = 0; i < provisoire.size() ; i++)
    {
        string strToTest = provisoire[i];
        bool testImportant = (strToTest.size() > 3 && str::checkIsAlphabet(strToTest)) //verif basic
                             && (
                                 str::isUpper(strToTest)                                //verif important
                                 || str::countOcurence(strToTest,file) >= 3
                             );

        if(testImportant)
            important.push_back(strToTest);
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

