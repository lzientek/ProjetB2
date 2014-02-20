#ifndef FICHIER_H
#define FICHIER_H
#define F_TEXTE 0
#define F_BINAIRE 1
#define F_HTML 2
#include <iostream>
#include "../Utils/Url.h"


using namespace std;


namespace Files
{
    class Fichier
    {
        public:

            Fichier(string nom="",string url="",string resume="",int type=F_TEXTE,double note=0,int taile=0,string textComplet="");

            virtual ~Fichier();

            //___________getter
            string getNom(){return nom;}
            utils::Url getURL(){return url;}
            string getResume(){return resume;}
            string getTextFull(){return textComplet;}
            string getExtention(){return extention;}
            double getNote(){return note;}
            string getType();
            int getTypeInt(){return type;}
            int getTaille(){return taille;}
            //___________fin getter
            bool isEmpty();

        protected:
        private:
            string getTitre();
            string nom;
            utils::Url url;
            string extention;
            string resume;
            string textComplet;
            double note;
            int taille;
            int type;

    };
}

#endif // FICHIER_H
