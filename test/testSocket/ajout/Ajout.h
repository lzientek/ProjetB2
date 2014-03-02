#ifndef AJOUT_H
#define AJOUT_H
#include <iostream>
#include <string>
#include <vector>
#include "../Files/Fichier.h"
#include "../Client/ClientHTTP.h"
#include "../Utils/Url.h"
#include "../Client/HTTPclientHeader.h"
#include "../Serveur.h"

namespace Add
{
    class Ajout
    {
        public:

            Ajout(string url);
            Ajout(string url,vector<string> oldUrls);
            Ajout(utils::Url url);
            virtual ~Ajout();
            void saveFiles();
        protected:
            vector<std::string> oldUrls;
            utils::Url url;
            Files::Fichier file;
        private:
    };
}
#endif // AJOUT_H
