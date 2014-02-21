#include "StringUtils.h"

using namespace std;

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


void utils::str::supprimerTousLesCharacteres(string &chaine, char c)
{
    chaine.erase(remove(chaine.begin(),chaine.end(),c)
                 ,chaine.end());
}

void utils::str::replaceAll(std::string& str, const std::string& from, const std::string& to)
{
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}


string utils::str::validXmlstring(string xml)
{
    string toRet=xml;
    replaceAll(toRet,"&","&amp;");
    replaceAll(toRet,"\"","&quot;");
    replaceAll(toRet,"'","&apos;");
    replaceAll(toRet,"<","&lt;");
    replaceAll(toRet,">","&gt;");
    return toRet;
}


int utils::str::calculNote(string text,string motImportant)
{
    return 2;//TODO (lucas): implémenter calcul note
}


/**
*@return les mots importants séparé par une virgule
**/
string utils::str::generateMotImportant(Files::Fichier file)
{
    //TODO (olivier): écrire cette fonction de taré
    return "lucas,zientek";
}



void utils::str::showFile(string path)
{
    ifstream fichier(stringToChar(path));  // on ouvre le fichier conf
    string actualLine;
    if(fichier.is_open())//si l'ouverture a réussi
        while(!fichier.eof()) //jusqu'a la fin du fichier
        {
            getline(fichier,actualLine); //on lis ligne par ligne
            cout<<actualLine<<endl;
        }
    fichier.close();
}
