#ifndef AJOUT_H
#define AJOUT_H
#include <iostream>
#include <string>
#include "../Files/Fichier.h"


namespace Add
{
    class Ajout
    {
        public:

            Ajout(string url);
            virtual ~Ajout();
        protected:
            std::string url;
            Files::Fichier file;
        private:
    };
}
#endif // AJOUT_H
