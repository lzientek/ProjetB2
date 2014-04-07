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

        do
        {
            client::ClientHTTP httpRequest(url,cookie);//on créé la requete http

            if(httpRequest.getResultStr() != "")
            {

                client::HTTPclientHeader header(httpRequest.getResultStr()); //on passe le resultat au header

                cookie = header.getCookies();//on met le cookie
                code = header.getHttpCode();//recuperre le code http (200 ok 404 etc...)
                string newUrl = header.getNewUrl();



                if(serv::Serveur::verbose) //si on est en mode verbeux on affiche les code et e=évntuelle redirection
                    cout<<"[ajout] code:"<<code<<" new url: "<<newUrl<<endl;



                //si aucune erreur
                if(code == 200)
                {

                    vector<string> urls = utils::str::getUrls(header.getTxt());

                    Files::Fichier fichierResultat("",
                                                   url.getUri(),
                                                   Algo::generateMotImportant(header.getTxt()),
                                                   header.getTypeInt(),
                                                   0,
                                                   header.getTaille(),
                                                   string(utils::str::stringToChar(header.getTxt()))
                                                  );



                    utils::RequetteBDD reqSQLPage,reqSQLurls;

                    if(!isCrawl)
                    {
                        reqSQLPage.add(fichierResultat);
                    }
                    else
                    {
                        reqSQLPage.update(fichierResultat,urlToSave);
                    }

                    utils::str::removeDuplicate(urls); //on supprime les doublons

                    reqSQLurls.add(urls);



                    if(serv::Serveur::verbose)
                    {
                        cout<<"[serv-add]enregistrement en bdd"<<endl;
                        cout<<"[serv-add] nombre de lien suivi:"<<urls.size()<<endl;
                    }

                    return 1;//success
                }
                else if( code > 300 && code < 400 && code != 304 && code != 305)
                {
                    if(newUrl.find("http")!=0)
                    {
                        if(newUrl!=oldNewUrl)
                        {
                            if(newUrl.find("/")==0 )
                                url = utils::Url(url.getUrl()+newUrl);
                            else
                                url = utils::Url(url.getUrl()+"/"+newUrl);
                        }
                        else
                        {
                            cleanBoucle();
                            cerr<<"[ajout]erreur boucle get "<<newUrl<<endl;
                            return -1;//error boucle
                        }
                    }
                    else if(url.getUri()!=newUrl) //on verifie bien qu'on boucle pas
                        url = utils::Url(newUrl);

                    else//si on boucle on break
                    {
                        cleanBoucle();
                        cerr<<"[ajout]erreur boucle uri "<<url.getUri()<<endl<<urlToSave<<endl<<newUrl<<endl;
                        return -1;//erreur boucle
                    }
                    oldNewUrl = newUrl;
                    if(serv::Serveur::verbose)
                        cout<<"[ajout] nouveau uri :"<<url.getUri()<<endl;
                }
                else
                {
                    cleanBoucle();
                    cerr<<"[Ajout]"<<url.getUri()<<" 404 error"<<endl;
                    return -1; //erreur boucle
                }
            }
            else return 0; //fichier vide


            i++;
        }
        while(code!=200 && code!=0 && i < MAX_REDIRECTION);

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
