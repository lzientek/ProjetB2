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
    int code = 200;
    do
    {
        client::ClientHTTP http(url);
        client::HTTPclientHeader header(http.getResultStr());
        cout<<header.getNewUrl()<<endl;
        code = header.getHttpCode();
        url = utils::Url(header.getNewUrl());
    }
    while(code!=200);

    return true;
}

Ajout::~Ajout()
{
    //dtor
}
