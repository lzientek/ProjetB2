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
    bool find=false;
    string urib = uri;
    unsigned findHttps = uri.find("https:");
    if(findHttps != string::npos)
    {
        //url = "https://";
        urib.erase(0,8+findHttps);//on enleve la premiere partie
        find = true;
    }
    else
    {
        unsigned findHttp = uri.find("http:");
        if(findHttp != string::npos)
        {
            //url = "http://";
            urib.erase(0,7+findHttp);//on enleve la premiere partie
            find = true;
        }
    }

    if(find)
    {

        unsigned findSlash = urib.find("/");
        if(findSlash != string::npos)
        {
            url = urib.substr(0,findSlash);
            get = urib.substr(findSlash,uri.size()-findSlash);
        }
        else
        {
            url=urib;
            get="/";
        }

    }
    else
    {
        url="";
        get="";
    }

}


Url::~Url()
{
    //dtor
}
