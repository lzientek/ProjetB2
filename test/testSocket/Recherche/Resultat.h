#ifndef Resultat_H
#define Resultat_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "../Files/Fichier.h"
#include "../Utils/RequetteBDD.h"

using namespace std;

namespace Recherche
{
    class Resultat
    {
        public:
            Resultat();
            Resultat(vector<string> words);
            virtual ~Resultat();
            void trier();
            string toXml();
            int search();
            void add(Files::Fichier file);
        protected:
        private:
            vector<string> words;
            string wordsStr;
            vector<Files::Fichier> files;


    };
}
#endif // Resultat_H
