#include "Ajout.h"

using namespace std;
using namespace Add;


Ajout::Ajout(string url,bool crawl)
{
    this->url = utils::Url(url);
    this->isCrawl = crawl;
    urlToSave=url;
}


Ajout::Ajout(utils::Url url,bool crawl)
{
    this->url = url;
    this->isCrawl = crawl;

    urlToSave=url.getUri();
}

int Ajout::saveFiles()
{

    if(url.isValid())
    {
        int code = 0;
        string oldNewUrl = "";
        string cookie="";
        int i=0;

        sf::Http req;

        req.SetHost(url.getUrl());

        request.SetURI(url.getGet());
        reponse = req.SendRequest(request);
        if(reponse.GetStatus() == sf::Http::Response::Ok)
        {
            std::string type = reponse.GetField("Content-Type");

            int t;
            if(type.find("text/html") != string::npos )
                t= F_HTML;
            else if(type.find("text/") != string::npos )
                t= F_TEXTE;
            else
                t= F_BINAIRE;
            if(t!=F_BINAIRE)
            {


                vector<string> urls = utils::str::getUrls(reponse.GetBody());

                Files::Fichier fichierResultat("",
                                               url.getUri(),
                                               Algo::generateMotImportant(reponse.GetBody()),
                                               t,
                                               0,
                                               reponse.GetBody().size(),
                                               string(reponse.GetBody())
                                              );



                utils::RequetteBDD reqSQLPage,reqSQLurls;

                if(!isCrawl)
                    reqSQLPage.add(fichierResultat);
                else
                    reqSQLPage.update(fichierResultat,urlToSave);


                utils::str::removeDuplicate(urls); //on supprime les doublons

                reqSQLurls.add(urls);
            }

        }

        return -2; //erreur trop de redirection
    }
    else
        cerr<<"[ajout]url non valid"<<endl;
    return -3; //url non valide

}

void Ajout::cleanBoucle()
{
    if(isCrawl)
    {
        utils::RequetteBDD req;
        req.update( Files::Fichier("erreur",url.getUri()),url.getUri(),(time(NULL)+3600*24*365));
        utils::RequetteBDD req1;
        req1.update( Files::Fichier("erreur",url.getUri()),urlToSave,(time(NULL)+3600*24*365));
    }
}


Ajout::~Ajout()
{
    //dtor
}
