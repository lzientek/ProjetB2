#include "Fichier.h"

using namespace Files;



Fichier::Fichier(string nom,string url,string resume,int type,double note,int taille,string textComplet) //ctor
{

    this->url = utils::Url(url);
    this->resume = resume;
    this->note = note;
    this->taille = taille;
    this->type = type;
    this->textComplet = textComplet;
    this->nom = nom;
    if(this->nom=="")
        this->nom = getTitre();
}


Fichier::~Fichier()
{
    //dtor
}

bool Fichier::isEmpty()
{
    return (nom=="" && !url.isValid());
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

string Fichier::getTitre()
{
    if(type == F_HTML)
    {
        //on recupere le texte dans la balise title
        string titre = "<title>",titreFin = "</title>";
        unsigned positionTitre = 0 , positionTitreFin =0;

        if((positionTitre = textComplet.find(titre)) != string::npos )
        {
            int debutTitre = positionTitre + titre.size();
            positionTitreFin = textComplet.find(titreFin);
            string realTitre = textComplet.substr(debutTitre,positionTitreFin-debutTitre);
            return realTitre;
        }
    }

    if(url.isValid())
    {
        unsigned nomFichierPosition = url.getGet().find_last_of("/\\"); // ne fonctionne pas comme find si besoin RTFM
        return url.getGet().substr(nomFichierPosition+1); //renvoie le nom du fichier
    }

    return "";
}
