#include "Crawl.h"
using namespace serv;

Crawl::Crawl()
{
    actualId = -1;
}


void Crawl::next()
{
    utils::RequetteBDD bdd;
    utils::Url urlArequeter = bdd.oldestCrawl(actualId);

    if(urlArequeter.isValid())
    {
        Add::Ajout nouvelleActu(urlArequeter);
        Files::Fichier file = nouvelleActu.getFile();
        bdd.update(actualId,file);
        if(Serveur::verbose)
            cout<<"[crawl] crawl effectuer sur :"<<urlArequeter.getUri()<<endl;
    }

}



Crawl::~Crawl()
{
    //dtor
}
