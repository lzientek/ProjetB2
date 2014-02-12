#include "Ajout.h"
using namespace std;
using namespace Add;

//TODO : beaucoup de chose

Ajout::Ajout(string url)
{
    this->url = utils::Url(url);
}



bool Ajout::getFile()
{

    //TODO: pas mal mais commenter + convertir to file puis enregistrer en base
    if(url.isValid())
    {
        int code = 0;
        do
        {
            client::ClientHTTP httpRequest(url);//on créé la requete http
            client::HTTPclientHeader header(httpRequest.getResultStr()); //on passe le resultat au header
            code = header.getHttpCode();//recuperre le code http (200 ok 404 etc...)
            if(serv::Serveur::verbose)
                cout<<"[ajout]"<<endl<<code<<header.getNewUrl()<<endl;

            url = utils::Url(header.getNewUrl());
        }
        while(code!=200 && code!=0);
    }
    return true;
}

Ajout::~Ajout()
{
    //dtor
}
