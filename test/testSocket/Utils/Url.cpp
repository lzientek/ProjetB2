#include "Url.h"

using namespace utils;
using namespace std;


Url::Url(string uri)
{
    this->uri = uri;
    url ="";
    parse();
}


void Url::parse()
{
    string urib = uri;

    unsigned findHttps = urib.find("https:");
    if(findHttps != string::npos)
    {
        urib.erase(0,8+findHttps);//on enleve la premiere partie
    }
    else
    {
        unsigned findHttp = urib.find("http:");
        if(findHttp != string::npos)
        {
            //url = "http://";
            urib.erase(0,7+findHttp);//on enleve la premiere partie
        }

    }

    unsigned findSlash = urib.find("/");
    if(findSlash != string::npos)
    {
        url = urib.substr(0,findSlash);
        get = urib.substr(findSlash,urib.size()-findSlash);
    }
    else
    {
        url=urib;
        get="/";
    }


}


Url::~Url()
{
    //dtor
}
