#include "HTTPclientHeader.h"

using namespace std;

using namespace client;

HTTPclientHeader::HTTPclientHeader(string header)
{
    this->header = header;
    httpCode = 0;
    newUrl = "";
    txt ="";
    parse();
}

HTTPclientHeader::~HTTPclientHeader()
{
    //dtor
}

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

            if( httpCode >= 200 && httpCode < 300 ) //si pas d'erreur
            {
                txt = header.substr(0, header.size());
                return true;
            }
            else if( httpCode > 300 && httpCode < 400 && httpCode != 304 && httpCode != 305 ) //redirection
            {
                for(unsigned i = 1; i < 6 && i < lignes.size(); i++) //on parcours le heeaderpour chercher la nouvelle location
                {
                    string lignePosition = lignes[i];
                    unsigned pos;
                    if(( pos = lignePosition.find(HTTP_LOCATION)) != string::npos) //si on trouve la vrai position du fichier on redirige
                    {
                        lignePosition.erase(0,pos+HTTP_LOCATION.size()); // on supprimme le location: pour avoir le nouveau lien
                        newUrl = lignePosition;
                        break;
                    }
                }
            }
            else
                cerr<<"[clientHttpHeader] erreur "<<httpCode<<endl;
        }
        else
            cerr<<"[clientHttpHeader] header incompatible"<<endl;
    }
    else
        cerr<<"[clientHttpHeader] aucun header"<<endl;

    return true;
}
