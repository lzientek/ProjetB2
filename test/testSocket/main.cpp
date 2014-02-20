#include "defines.h"
#include "Client/ClientHTTP.h"

using namespace std;



int main(int argc, char *argv[])
{

    utils::str::showFile("demarage");

    //chargement des modules statics
    utils::Conf::load();
    utils::Stats::load();
    utils::Conf::stopCrawl = true;//probleme de crawl
    utils::Processus procs;


    return 0;
}






