#include "Ajout.h"
using namespace std;
using namespace Add;


Ajout::Ajout(string url)
{
    this->url = utils::Url(url);
}
Ajout::Ajout(string url,vector<string> &oldUrls)
{
    this->url = utils::Url(url);
    this->oldUrls = oldUrls;
}
Ajout::Ajout(utils::Url url)
{
    this->url = url;
}

void Ajout::saveFiles()
{


    if(url.isValid())
    {
        int code = 0;
        do
        {
            client::ClientHTTP httpRequest(url);//on créé la requete http



            if(httpRequest.getResultStr() != "")
            {
                client::HTTPclientHeader header(httpRequest.getResultStr()); //on passe le resultat au header

                code = header.getHttpCode();//recuperre le code http (200 ok 404 etc...)

                if(serv::Serveur::verbose) //si on est en mode verbeux on affiche les code et e=évntuelle redirection
                    cout<<"[ajout] code:"<<code<<" new url: "<<header.getNewUrl()<<endl;


                if(code == 200)
                {

                    vector<string> urls = utils::str::getUrls(header.getTxt(),url.getUrl());




                    Files::Fichier fichierResultat("",
                                                   url.getUri(),
                                                   utils::str::generateMotImportant(header.getTxt()),
                                                   header.getTypeInt(),
                                                   0,
                                                   header.getTaille(),
                                                   string(utils::str::stringToChar(header.getTxt()))
                                                  );



                    utils::RequetteBDD reqSQLPage,reqSQLurls;
                    reqSQLPage.add(fichierResultat);

                    utils::str::removeDuplicate(urls); //on supprime les doublons

                    reqSQLurls.add(urls);

                    if(serv::Serveur::verbose)
                    {
                        cout<<"[serv-add]enregistrement en bdd"<<endl;
                        cout<<"[serv-add] nombre de lien suivi:"<<urls.size()<<endl;
                    }

                    break;
                }


                if(header.getNewUrl().find("/")==0)
                {
                    if(header.getNewUrl()!=url.getGet())
                        url = utils::Url(url.getUrl()+header.getNewUrl());

                    else
                    {
                        cerr<<"[ajout]erreur boucle get"<<endl;
                        break;
                    }

                }
                else if(url.getUri()!=header.getNewUrl()) //on verifie bien qu'on boucle pas
                    url = utils::Url(header.getNewUrl());

                else//si on boucle on break
                {
                    cerr<<"[ajout]boucle error"<<endl;
                    break;
                }

            }
            else
                break;



        }
        while(code!=200 && code!=0);
    }
    else
        cerr<<"[ajout]url non valid"<<endl;

}



Ajout::~Ajout()
{
    //dtor
}
