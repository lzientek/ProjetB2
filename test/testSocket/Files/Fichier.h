#ifndef FICHIER_H
#define FICHIER_H
#define F_TEXTE 0
#define F_BINAIRE 1
#define F_HTML 2
#include <iostream>

using namespace std;


namespace Files
{
    class Fichier
    {
        public:

            Fichier(string nom="",string url="",string resume="",int type=F_TEXTE,double note=0,int taile=0);

            virtual ~Fichier();


            string getNom(){return nom;}
            string getURL(){return url;}
            string getResume(){return resume;}
            string getExtention(){return extention;}
            double getNote(){return note;}
            string getType();
            int getTaille(){return taille;}
        protected:
        private:
            string nom;
            string url;
            string txt;
            string extention;
            string resume;
            double note;
            int taille;
            int type;

    };
}

#endif // FICHIER_H
