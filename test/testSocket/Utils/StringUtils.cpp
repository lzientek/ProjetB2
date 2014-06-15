#include "StringUtils.h"
#include <boost/regex.hpp>

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
    for(uint i=0; i<motsRecherche.size(); i++)
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

string utils::str::regex_replace(string reg,string text,string par)
{

    boost::regex e (reg);   // matches words beginning by "sub"

    std::ostringstream  os;


    std::ostream_iterator<char, char> out(os);
    boost::regex_replace(out, text.begin(), text.end(),
                         e, par, boost::match_default | boost::format_all);
    return os.str();
}

vector<string> utils::str::getUrls(string text)
{
    vector<string> urlAretourner;
    unsigned pos = 0;

    while((pos = text.find("href=\"",pos)) != string::npos)
    {
        pos+=string("href=\"").length();
        unsigned fin = text.find_first_of(" \"" ,pos);
        if( (fin-pos) > 12)//taille minimal d'une url
        {
            string urlToSave =text.substr(pos,fin-pos);

            if(urlToSave.find("http")==0) //si on a bien une addresse valide
            {

                urlAretourner.push_back(urlToSave);
            }

        }

        pos = fin;
    }

    return urlAretourner;
}


void utils::str::removeDuplicate(vector<string> &tab)
{
    sort(tab.begin(), tab.end());
    tab.erase( unique (tab.begin(), tab.end()),tab.end());
    //VerifUrl(tab);
}


void utils::str::VerifUrl(vector<string> &urls)
{

//    for(uint i = 0; i < urls.size(); i++)
//    {
//        if()
//            urls.erase(i));
//    }
}


bool utils::str::isUpper(string str)
{
    std::string str1 = str;
    std::transform(str1.begin(), str1.end(),str1.begin(), ::toupper);
    if(str==str1)
        return true;
    return false;
}


bool utils::str::checkIsAlphabet(string str)
{
    char* tabStr = stringToChar(str);
    for(uint i = 0; i<str.size(); i++)
        if(tabStr[i] < 'A' && tabStr[i] > 'Z' && tabStr[i] < 'a' && tabStr[i] > 'z')
            return false;// si on a des char qui ne sont pas des lettres
    return true;
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

string utils::str::interieurBalise(string str,string nomBalise)
{
    string titre = "<"+nomBalise+">",titreFin = "</"+nomBalise+">";
    unsigned positionTitre = 0 , positionTitreFin =0;

    if((positionTitre = str.find(titre)) != string::npos )
    {
        int debutTitre = positionTitre + titre.size();
        positionTitreFin = str.find(titreFin);
        string text = str.substr(debutTitre,positionTitreFin - debutTitre);
        return text;
    }
    return "";
}
