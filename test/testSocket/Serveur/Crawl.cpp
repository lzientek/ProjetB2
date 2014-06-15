#include "Crawl.h"
using namespace serv;

std::string Crawl::GetNextUrl()
{
    ifstream fichier("tocrawl");
    string actualLine;
    if(fichier.is_open())//si l'ouverture a réussi
        while(!fichier.eof()) //jusqu'a la fin du fichier
        {
            getline(fichier,actualLine); //on lis ligne par ligne
            return actualLine;
        }
    fichier.close();
}


void Crawl::SetNextUrl(std::string url)
{
    ofstream fichierStats("tocrawl",ios::out | ios::trunc);  // on ouvre le fichier conf

    if(fichierStats.is_open())//si l'ouverture a réussi
    {
        fichierStats<<url<<endl;
        fichierStats.close();
    }
}


Crawl::Crawl()
{

    actualId = -1;
}


void Crawl::next()
{
    string urlNcrawl = GetNextUrl();

    if(urlNcrawl!="")
    {
        utils::str::supprimerTousLesCharacteres(urlNcrawl,' ');
        Add::Ajout nouvelleActu(urlNcrawl);
        nouvelleActu.saveFiles();
        SetNextUrl("");
    }
    else
    {
        utils::RequetteBDD bdd;
        string urlArequeter = bdd.oldestCrawl();

        if(urlArequeter!="")
        {
            Add::Ajout nouvelleActu(urlArequeter,true);
            nouvelleActu.saveFiles();
        }

        actualId++;
    }
}



Crawl::~Crawl()
{
    //dtor
}
