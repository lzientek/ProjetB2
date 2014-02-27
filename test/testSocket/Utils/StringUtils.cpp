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

void utils::str::replaceAll(string& str, const string& from, const string& to)
{
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != string::npos)
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


int utils::str::calculNote(vector<string> motsRecherche,string text,string motImportant)
{
    int note = 0;
    for(int i=0; i<motsRecherche.size(); i++)
    {
        string mot = motsRecherche[i];
        supprimerTousLesCharacteres(mot,' ');//on supprime l'espace inutile
        if(mot.length()>2)
        {
            int nbDsText = countOcurence(mot,text);
            int nbDsMotImportant = countOcurence(mot,motImportant);

            int noteProvisoir = (nbDsMotImportant * COEF_IMPORTANCE_MOT_IMPORTANT) + nbDsText;
            if(mot.length()<=4) //si le mot est petit un divise par deux les points
                noteProvisoir = noteProvisoir / 2;
            note += noteProvisoir;
        }
    }

    return note;//TODO (lucas): approfondir calcul note
}


vector<string> utils::str::getUrls(string text)
{
    vector<string> urlAretourner;

    unsigned pos = 0;

    while((pos = text.find("http://",pos)) != string::npos || (pos = text.find("https://",pos)) != string::npos)
    {

        unsigned fin = text.find_first_of(" \"\'\\" ,pos);
        if( (fin-pos) > 12)//taille minimal d'une url
            urlAretourner.push_back(text.substr(pos,fin-pos));

        pos =fin;
    }



    return urlAretourner;
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


int utils::str::countOcurence(string mot, string dans)
{
    int nombre = 0;
    unsigned pos = 0;

    while((pos = dans.find(mot,pos)) != string::npos)
    {
        nombre++;
        pos += mot.size();
    }

    return nombre;
}
