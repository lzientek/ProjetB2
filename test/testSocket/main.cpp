#include "defines.h"
#include "Client/ClientHTTP.h"
#include "Files/Fichier.h"
using namespace std;



int main(int argc, char *argv[])
{

    utils::str::showFile("demarage");

    //chargement des modules statics
    utils::Conf::load();
    utils::Stats::load();
    utils::Conf::stopCrawl = true;//probleme de crawl

    //string s = "à";
    //cout<<utils::str::stringToChar(s)[0]<<(int) utils::str::stringToChar(s)[1]<<endl;
    utils::Processus procs;


    return 0;
}






