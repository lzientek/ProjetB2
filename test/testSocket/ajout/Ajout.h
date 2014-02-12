#ifndef AJOUT_H
#define AJOUT_H
#include <iostream>
#include <string>
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
            virtual ~Ajout();
            bool getFile();
        protected:
            utils::Url url;
            Files::Fichier file;
        private:
    };
}
#endif // AJOUT_H
