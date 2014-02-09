#include "HttpHeader.h"

using namespace std;
using namespace serv;
using namespace utils;

HttpHeader::HttpHeader() {}

HttpHeader::HttpHeader(string header)
{
    cheminRequete = ERROR404; //chemin par default

    this->header = header;
    parse(); //parsing du header
}

HttpHeader::HttpHeader(char* header)
{
    cheminRequete = ERROR404;//chemin par default
    string strg(header);
    this->header = strg;
    parse(); //parsing du header
}


bool HttpHeader::parse()
{
    vector<string> lignes = str::split(header,RETOURLIGNE); //pour faire du ligne par ligne

    if(lignes.size() > 0) //recupération du get de la premiere ligne
    {
        string lineGET = lignes[0];
        unsigned posEnd = lineGET.find(HTTP_PROTOCOLE);
        if( lineGET.find("GET") != string::npos )//si le GET est bien présent
        {
            cheminRequete = lineGET.substr(4,posEnd-4);
            parseChemin();
        }

        if(serv::Serveur::verbose)
            cout<<"chemin requete: "<<cheminRequete<<endl<<"action: "<<action<<endl;
    }
    else
        return false;

    return true;
}


bool HttpHeader::parseChemin()
{
    if(cheminRequete != ERROR404)
    {
        vector<string> vectStr = str::split(cheminRequete,"/");
        action = vectStr[0];
        vectStr.erase( vectStr.begin() ); //on supprime le premier

        if(vectStr.size()>0)
            keys = vectStr;
    }
    return true;
}


/**
* toujours utilisé les DEFINES A_*
**/
int HttpHeader::getAction()
{
    if(action == "recherche")
        return A_RECHERCHE;
    else if(action == "ajout")
        return A_AJOUT;
    else
    {
        cheminRequete = ERROR404;
        return A_404ERROR;
    }
}

string HttpHeader::getChemin()
{
    string returnValue = "";
    for(unsigned i = 0; i < keys.size(); i++)
        returnValue += keys[i];
    return returnValue;
}

vector<string> HttpHeader::getKeys()
{
    return keys;
}


HttpHeader::~HttpHeader()
{
    //dtor
}


