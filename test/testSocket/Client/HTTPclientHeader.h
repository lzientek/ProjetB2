#ifndef HTTPCLIENTHEADER_H
#define HTTPCLIENTHEADER_H
#include "../defines.h"
#include "../Utils/StringUtils.h"
#include "../Files/Fichier.h"


using namespace std;
namespace client
{
    class HTTPclientHeader
    {
            const string HTTP_PROTOCOLE = "HTTP/1.1 ";
            const string HTTP_LOCATION = "Location: ";
            const string HTTP_TYPE = "Content-Type: ";
            const string HTTP_TAILLE = "Content-Length: ";

        public:
            HTTPclientHeader(string header);

            //_______getter
            string getNewUrl() { return newUrl; }
            string getType() {return type;}
            int getTypeInt();
            int getHttpCode(){return httpCode;}
            int getTaille(){return taille;}
            string getTxt(){return txt;}
            //______fingetter

            virtual ~HTTPclientHeader();
        protected:
        private:
            string getContentFromHeader(string mot,vector<string> lignes);
            bool parse();
            string header;
            int httpCode;
            string url;
            string newUrl;
            string txt;
            string type;
            int taille;
    };
}
#endif // HTTPCLIENTHEADER_H
