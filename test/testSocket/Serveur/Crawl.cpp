#include "Crawl.h"
using namespace serv;

Crawl::Crawl()
{
    actualId = -1;
}


void Crawl::next()
{
    utils::RequetteBDD bdd;
    utils::Url urlArequeter = bdd.oldestCrawl();
    actualId++;
    if(urlArequeter.isValid())
    {
        Add::Ajout nouvelleActu(urlArequeter);
        nouvelleActu.saveFiles();

        //else
            cerr<<"[crawl] non effectuer erreur file!"<<endl;


    }

}



Crawl::~Crawl()
{
    //dtor
}
