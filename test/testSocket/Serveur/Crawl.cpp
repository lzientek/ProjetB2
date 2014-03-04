#include "Crawl.h"
using namespace serv;

Crawl::Crawl()
{
    actualId = -1;
}


void Crawl::next()
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



Crawl::~Crawl()
{
    //dtor
}
