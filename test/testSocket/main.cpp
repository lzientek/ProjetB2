#include "defines.h"
#include "Client/ClientHTTP.h"

using namespace std;



int main(int argc, char *argv[])
{
    cout<< "_______________________________" <<endl;
    cout<< "|   [Projet search engine!]   |"<<endl;
    cout<< "|_____________________________|"<<endl;

    //chargement des modules statics
    utils::Conf::load();
    utils::Stats::load();
    Add::Ajout client("http://www.google.com/");
    client.getFile();
    //utils::Processus procs;


    return 0;
}






