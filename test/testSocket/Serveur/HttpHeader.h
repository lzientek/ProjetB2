#ifndef HttpHeader_H
#define HttpHeader_H

#define A_RECHERCHE 0
#define A_AJOUT 1
#define A_404ERROR 42


#include <iostream>
#include <string>
#include <vector>
#include "../Utils/StringUtils.h"
#include "../Serveur.h"

using namespace std;

namespace serv
{
    const string ERROR404 = "/404";
    const string HTTP_PROTOCOLE = "HTTP/1.1";


    class HttpHeader
    {
        public:
            HttpHeader();
            HttpHeader(string header);
            HttpHeader(char* header);
            int getAction();
            string getChemin();
            vector<string> getKeys();
            virtual ~HttpHeader();
        protected:
        private:
            bool parse();
            bool parseChemin();
            string header;
            string action;
            string cheminRequete;
            string keys;
            bool method;
    };
}



#endif // HttpHeader_H
