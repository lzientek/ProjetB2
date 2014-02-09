#include "Resultat.h"

using namespace Recherche;
using namespace std;

Resultat::Resultat() {}

Resultat::Resultat(vector<string> words)
{
    this->words = words;
    for(int i = 0; i<words.size();i++)
        wordsStr += words[i] + " ";
    search();
}


int Resultat::search()
{
    utils::RequetteBDD req;
    files = req.search(this->words);
    return 0;
}

//TODO:   mettre en privé sert juste pour le debogage
void Resultat::add(Files::Fichier file)
{
    files.insert(files.end(),file);
}


string Resultat::toXml()
{

    stringstream streamToRet("");
    streamToRet << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<endl;
    streamToRet << "<results search=\""<< wordsStr <<"\" >"<<endl;

    for(unsigned int i=0; i<files.size(); i++) //pour chaque objet une nouvelle balise xml
    {
        streamToRet<<"<file type=\""<< files[i].getType() <<"\">";

        streamToRet<<"<titre>";
        streamToRet<< files[i].getNom();
        streamToRet<<"</titre>"<<endl;

        streamToRet<<"<url>";
        streamToRet<< files[i].getURL();
        streamToRet<<"</url>";

        streamToRet<<"<note>";
        streamToRet<< files[i].getNote();
        streamToRet<<"</note>";

        streamToRet<<"<resume>";
        streamToRet<< files[i].getResume();
        streamToRet<<"</resume>";

        streamToRet<<"</file>";
    }
    streamToRet<<"</results>"<<endl;
    return streamToRet.str();
}

Resultat::~Resultat()
{
    //dtor
}
