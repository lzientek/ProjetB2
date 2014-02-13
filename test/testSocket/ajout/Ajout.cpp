#include "Ajout.h"
using namespace std;
using namespace Add;

//TODO : beaucoup de chose

Ajout::Ajout(string url)
{
    this->url = utils::Url(url);
}


Files::Fichier Ajout::getFile()
{

    //TODO: pas mal mais commenter + convertir to file puis enregistrer en base
    if(url.isValid())
    {
        int code = 0;
        do
        {
            client::ClientHTTP httpRequest(url);//on créé la requete http
            if(httpRequest.getResultStr()!="")
            {
                client::HTTPclientHeader header(httpRequest.getResultStr()); //on passe le resultat au header

                code = header.getHttpCode();//recuperre le code http (200 ok 404 etc...)

                if(serv::Serveur::verbose) //si on est en mode verbeux on affiche les code et e=évntuelle redirection
                    cout<<"[ajout] code:"<<code<<" new url: "<<header.getNewUrl()<<endl;


                if(code==200)
                {
                    return Files::Fichier(url.getGet(),
                                          url.getUri(),
                                          utils::str::generateMotImportant(header.getTxt()),
                                          header.getTypeInt(),
                                          0,
                                          header.getTaille(),
                                          header.getTxt()
                                         );

                }
                if(url.getUri()!=header.getNewUrl())
                    url = utils::Url(header.getNewUrl());
                else
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
    return Files::Fichier();
}


Ajout::~Ajout()
{
    //dtor
}
