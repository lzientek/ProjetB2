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
    utils::Processus procs;


    return 0;
}






