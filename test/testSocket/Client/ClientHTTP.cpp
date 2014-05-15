#include "ClientHTTP.h"
using namespace std;
using namespace client;



ClientHTTP::ClientHTTP(utils::Url &uri,string cookies)
{
    urlClient = uri;
    file = "";
    this->cookies = cookies;
    if(urlClient.isValid())
    {
        if(execute() < 0)
            file= "";
    }
    else
        cerr<<"[clientHttp]error url :"<<uri.getUri()<<endl;
}



ClientHTTP::~ClientHTTP()
{
    //dtor
}
