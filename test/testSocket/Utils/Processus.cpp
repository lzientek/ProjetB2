#include "Processus.h"

using namespace utils;
using namespace std;

Processus::Processus()
{

    cout<<"[prog]demarrage des processus"<<endl;
//TODO:un try catch
    thread threadServeur(runServeur);
    thread threadCrawl(runCrawl );
    thread threadCmd(runCommande );
    threadServeur.join();
    threadCrawl.join();
    threadCmd.join();


}


void Processus::stopAll()
{
    cout<<"[prog]Arret des processus"<<endl;
    Conf::setQuitter(true);
}




Processus::~Processus()
{
    //dtor
}


//--------------------------------------fin class Processus
//fonction de lancement des threads
//--------------------------------------------------------//


void utils::runServeur()
{

    cout<<"[serv]lancement du serveur..."<<endl;
    serv::Serveur serv(stoi(Conf::getConf("portServeur")));//creation du serv

    if(!serv.getError()) //si aucune erreur a la creation des socket
        cout<<"[serv]serveur lancé!"<<endl;
    else
    {
        cout<<"[serv]fatal error!"<<endl;
        Conf::setQuitter(true);
    }


    bool boucle = !Conf::getQuitter();
    while(boucle) //on ecoute tant ue c'est vrai
    {
        boucle = serv.ecoute() && !Conf::getQuitter();
    }

    serv.closeSocket(); //on quite proprement
    cout<<"[serv]serveur arreté!"<<endl;
}




void utils::runCrawl()
{
    cout<<"[crawl]lancement du crawl"<<endl;
//TODO : creation du crawl
    cout<<"[crawl]arret du crawl"<<endl;
}




void utils::runCommande()
{
    cout<<"[cmd]lancement du systeme de commande..."<<endl;
    cout<<"[cmd]systeme de commande lancé.(help pour plus d'aide)"<<endl;

    bool boucle =true;
    while(boucle && !Conf::getQuitter())
    {
        boucle = cmd();
    }
    Conf::setQuitter(true);
    cout<<"[cmd]arret cmd"<<endl;
}



bool utils::cmd()
{
    string commande;
    bool boucle = true;

    //console
    cout<<"cmd>"<<flush;
    getline(cin,commande);

    //on split pour les différents arguments
    vector<string> args = str::split(commande," ");
    if(args.size() > 0)
        commande = args[0];


    //gros if tout moche car pas de switch pour les string

    if(commande == "exit")
    {
        cout<<"[prog]Le programme va quitter."<<endl;
        boucle = false;
    }


    else if(commande == "reloadconf")
        utils::Conf::reload();



    else if(commande == "clear")
        system("clear");


    else if(commande == "port")
        cout<<"Port serveur:"<<Conf::getConf("portServeur")<<endl;


    else if(commande == "resolvError")
    {
        ifstream fichieraddon("addon", ios::in);  // on ouvre le fichier conf
        string actualLine;
        if(fichieraddon)//si l'ouverture a réussi
            while(!fichieraddon.eof()) //jusqu'a la fin du fichier
            {
                getline(fichieraddon,actualLine); //on lis ligne par ligne
                cout<<actualLine<<endl;
            }
        fichieraddon.close();
    }



    else if(commande == "connection")
    {
        if(args.size()>1)
        {

            if(args[1]=="show")
                serv::Serveur::verbose = true;
            else if(args[1]=="hide")
                serv::Serveur::verbose = false;
            else
                cout<<args[1]<<" n'est pas valide pour connection"<<endl;
        }
        else
            serv::Serveur::verbose = !serv::Serveur::verbose;
    }



    else if(commande == "help" || commande == "?")
    {
        cout<<"Commande utilisable:"<<endl;
        cout<<"help | ? : Cette page"<<endl;
        cout<<"exit : Fermer le programme"<<endl;
        cout<<"reloadconf : pour charger la conf de nouveau"<<endl;
        cout<<"clear : clear l'écran"<<endl;
        cout<<"connection [show|hide] : affiche les connections du serveur"<<endl;
        cout<<"port : affiche le port utilisé par le serveur"<<endl;
        cout<<"resolvError : affiche comment resoudre les erreurs"<<endl;
        //TODO : implementer pour chaque nouvelle commande et p⁻e le mettre dans un fichier
    }

    else
        cout<<"La commande "<<commande<< " n'éxiste pas. (help pour voir les commandes)"<<endl;

    return boucle;
}
