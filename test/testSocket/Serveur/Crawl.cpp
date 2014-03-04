#include "Crawl.h"
using namespace serv;

Crawl::Crawl()
{
    actualId = -1;
}


void Crawl::next()
{
    sleep(stoi(utils::Conf::getConf("tempsEntreCrawl")) );
    utils::RequetteBDD bdd;
    string urlArequeter = bdd.oldestCrawl();
    actualId++;
    if(urlArequeter!="")
    {
        Add::Ajout nouvelleActu(urlArequeter,true);
        nouvelleActu.saveFiles();
    }


}



Crawl::~Crawl()
{
    //dtor
}
