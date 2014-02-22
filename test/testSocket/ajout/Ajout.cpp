#include "Ajout.h"
using namespace std;
using namespace Add;



Ajout::Ajout(string url)
{
    this->url = utils::Url(url);
}

Ajout::Ajout(utils::Url url)
{
    this->url = url;
}

Files::Fichier Ajout::getFile()
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
                    return Files::Fichier("",
                                          url.getUri(),
                                          utils::str::generateMotImportant(header.getTxt()),
                                          header.getTypeInt(),
                                          0,
                                          header.getTaille(),
                                          header.getTxt()
                                         );

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
    return Files::Fichier();
}



Ajout::~Ajout()
{
    //dtor
}
