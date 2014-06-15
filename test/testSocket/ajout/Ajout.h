#ifndef AJOUT_H
#define AJOUT_H
#define MAX_REDIRECTION 4
#include <iostream>
#include <string>
#include <vector>
#include "../Files/Fichier.h"
#include <SFML/Network.hpp>

#include "../Utils/Url.h"
#include "../Client/HTTPclientHeader.h"



namespace Add
{
class Ajout
{
public:

    Ajout(string url,bool crawl = false);

    Ajout(utils::Url url,bool crawl = false);
    virtual ~Ajout();
    int saveFiles();
protected:
    utils::Url url;
    Files::Fichier file;
    bool isCrawl;
private:
    sf::Http req;
    sf::Http::Request request;
    sf::Http::Response reponse;
    void cleanBoucle();
    std::string urlToSave;
};
}
#endif // AJOUT_H
