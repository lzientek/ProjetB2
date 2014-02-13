#include "Fichier.h"

using namespace Files;



Fichier::Fichier(string nom,string url,string resume,int type,double note,int taille,string textComplet) //ctor
{
    this->nom = nom;
    this->url = url;
    this->resume = resume;
    this->note = note;
    this->taille = taille;
    this->type = type;
    this->textComplet = textComplet;
}


Fichier::~Fichier()
{
    //dtor
}

bool Fichier::isEmpty()
{
    return (nom=="" && url=="");
}

string Fichier::getType()
{
    switch(type) //on retourne les strings des types pour le xml
    {
        case F_TEXTE:
            return "txt";
            break;
        case F_BINAIRE:
            return "bin";
            break;
        case F_HTML:
            return "html";
            break;
        default:
            return "file";
            break;
    }
}
