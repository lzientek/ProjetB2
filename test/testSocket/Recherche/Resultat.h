#ifndef Resultat_H
#define Resultat_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "../Files/Fichier.h"
#include "../Utils/RequetteBDD.h"
#include "../Utils/Url.h"
#include "../Utils/StringUtils.h"


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

protected:
private:
    void add(Files::Fichier file);
    vector<string> words;
    string wordsStr;
    vector<Files::Fichier> files;


};
}
#endif // Resultat_H
