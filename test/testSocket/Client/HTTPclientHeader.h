#ifndef HTTPCLIENTHEADER_H
#define HTTPCLIENTHEADER_H
#include "../defines.h"
#include "../Utils/StringUtils.h"


namespace client{
class HTTPclientHeader
{
    const string HTTP_PROTOCOLE = "HTTP/1.1 ";
    const string HTTP_LOCATION = "Location: ";
    public:
        HTTPclientHeader(std::string header);
        std::string getNewUrl(){return newUrl;}
        int getHttpCode(){return httpCode;}
        virtual ~HTTPclientHeader();
    protected:
    private:
    bool parse();
    std::string header;
    int httpCode;
    std::string newUrl;
    std::string txt;
};
}
#endif // HTTPCLIENTHEADER_H
