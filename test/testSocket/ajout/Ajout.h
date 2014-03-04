#ifndef AJOUT_H
#define AJOUT_H
#define MAX_REDIRECTION 4
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

            Ajout(string url,bool crawl = false);

            Ajout(utils::Url url,bool crawl = false);
            virtual ~Ajout();
            int saveFiles();
        protected:
            utils::Url url;
            Files::Fichier file;
            bool isCrawl;
        private:
            std::string urlToSave;
            void cleanBoucle();
    };
}
#endif // AJOUT_H
