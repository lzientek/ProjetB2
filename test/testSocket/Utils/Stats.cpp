#include "Stats.h"

using namespace std;
using namespace utils;

int Stats::nbRequeteServeur;
std::string Stats::actualAction;

void Stats::load()
{
    nbRequeteServeur=0;
    actualAction="";
}

int Stats::getNbRequeteServ()
{
    return nbRequeteServeur;
}

void Stats::incRequeteServ(int act,string key)
{
    nbRequeteServeur++;
    ostringstream stream;
    stream << act << ":"<<key;
    actualAction = stream.str();
    save();
}


void Stats::save()
{
    save(Conf::getConf("statFile"));
}


void Stats::save(string fileName)
{
    ofstream fichierStats(fileName,ios::app);  // on ouvre le fichier conf

    if(fichierStats.is_open())//si l'ouverture a réussi
    {
        fichierStats<<time(NULL)<<":"<<nbRequeteServeur<<":"<<actualAction<<endl;
        fichierStats.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier stats!" << endl;

}
