#include "HTTPclientHeader.h"

using namespace std;

using namespace client;

HTTPclientHeader::HTTPclientHeader(string header)
{
    this->header = header;
    httpCode = 0;
    taille=0;
    newUrl = "";
    txt ="";
    parse();
}


HTTPclientHeader::~HTTPclientHeader()
{
    //dtor
}

//getter spéciale

int HTTPclientHeader::getTypeInt()
{
    if(type.find("text/html") != string::npos )
        return F_HTML;
    else if(type.find("text/") != string::npos )
        return F_TEXTE;
    else
        return F_BINAIRE;
}



//_____________methode private

bool HTTPclientHeader::parse()
{

    vector<string> lignes = utils::str::split(header,"\r\n"); //pour faire du ligne par ligne

    if( lignes.size() > 0 ) //si on a des lignes
    {
        string ligne  = lignes[0]; //premiere ligne du header avec les reponses
        if(ligne.find(HTTP_PROTOCOLE) == 0)
        {
            ligne.erase(0, HTTP_PROTOCOLE.size()); // on supprimmele protocole
            httpCode = stoi(ligne.substr(0, 3)); //on recupère le code

            type = getContentFromHeader(HTTP_TYPE,lignes);//on recupere le type


            string provTaille = getContentFromHeader(HTTP_TAILLE,lignes);//on recupere la taille provisoirement
            if(provTaille == "")
                taille=0;
            else
                taille = stoi(provTaille);


            if( httpCode >= 200 && httpCode < 300 ) //si pas d'erreur
            {
                //TODO: virer le header (et je galere vraiment);

                cout<<"txt:"<<txt<<endl;
                return true;
            }

            else if( httpCode > 300 && httpCode < 400 && httpCode != 304 && httpCode != 305 ) //redirection
                newUrl = getContentFromHeader(HTTP_LOCATION,lignes); //on recupere la nouvelle url en cas de rediretion

            else
                cerr<<"[clientHttpHeader] erreur "<<httpCode<<endl;
        }
        else
            cerr<<"[clientHttpHeader] header incompatible"<<endl;
    }
    else
        cerr<<"[clientHttpHeader] aucun header"<<endl;

    return false;
}


/**
*@return " si introuvé
**/
string HTTPclientHeader::getContentFromHeader(string mot,vector<string> lignes)
{
    string result("");
    for(unsigned i = 0; i < 30 && i < lignes.size(); i++) //on parcours le heeaderpour trouver le type
    {
        unsigned pos;
        if(( pos = lignes[i].find(mot)) != string::npos) //si on trouve la vrai position du fichier on redirige
        {
            result = lignes[i].substr(pos+mot.size(),lignes[i].size()-(pos+mot.size())); // on supprimme le location: pour avoir le nouveau lien
            return result;
        }
    }
    return "";
}


//________fin methode private

