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
            cheminRequete = lineGET.substr(5,posEnd-5);
            parseChemin();

            if(serv::Serveur::verbose)
                cout<<"[serHeader]chemin requete: "<<endl
                    <<lineGET<<endl
                    <<"action: "<<action<<endl;
        }
    }
    else
        return false;

    return true;
}


bool HttpHeader::parseChemin()
{
    if(cheminRequete != ERROR404)
    {
        unsigned vectStr = cheminRequete.find("?");
        if(vectStr != string::npos)
        {
            action = cheminRequete.substr(0,vectStr);
            keys = cheminRequete.substr(vectStr +1 ); //+1pour pas prendre le ?
        }

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
    else if(action == "add")
        return A_AJOUT;
    else
    {
        cheminRequete = ERROR404;
        return A_404ERROR;
    }
}

string HttpHeader::getChemin()
{
    return keys;
}

vector<string> HttpHeader::getKeys()
{
    return str::split(keys,"&");
}


HttpHeader::~HttpHeader()
{
    //dtor
}


