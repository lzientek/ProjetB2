#include "Serveur.h"
#include "Serveur/HttpHeader.h"


using namespace std;

using namespace serv;

bool Serveur::verbose;

Serveur::Serveur()
{
    Serveur(8080);
}




Serveur::Serveur(int port)
{
    error = false;
    portno = port;
    verbose = false;

    sockfd = socket(AF_INET, SOCK_STREAM, 0); //on crée le socket

    if (sockfd < 0)
    {
        cerr<<"ERROR opening socket"<<endl;
        error = true;
    }


    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY; //réseau locl
    serv_addr.sin_port = htons(portno);//attribution du port

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)//écoute (mode serveur)
    {
        cerr<<"ERROR on binding"<<endl;
        error = true;
    }


    listen(sockfd,10);//écoute

    if (fcntl(sockfd, F_SETFL, O_NDELAY) < 0)
    {
        cerr<<"Can't set socket to non-blocking";
        error = true;
    }

}




bool Serveur::ecoute()
{
    if(error)
        return false;

    bzero(buffer,BUFFER_SYZE);
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);

    if (read(newsockfd, buffer, BUFFER_SYZE) == -1) //si aucune connection
    {
        sleep(1);
    }
    else
    {
        if(verbose)
            cout<<"envoie rep"<<endl;
        envoieReponse();
    }

    close(newsockfd);

    //si aucune erreur on continue l'écoute
    return !error; //TODO : better (exeption)
}



void Serveur::envoieReponse()
{
    HttpHeader header(buffer);

    u_int action = header.getAction();
    string rep = HTTP404;

    if(verbose) //si le mode verbose est activé
        cout<<"action:"<<endl<<action<<endl;

    if(action !=A_404ERROR)
    {
        if(action ==A_RECHERCHE) //si l'utilisateur fais une recherche
        {
            Recherche::Resultat resultRecherche = Recherche::Resultat(header.getKeys()); // on passe les arguments de recherche du header a a recherche
            rep = HTTPOK;//on met le header
            rep += resultRecherche.toXml();
        }

        else if( action == A_AJOUT ) //si il veut ajouter une url
        {
            Add::Ajout nouvelleAjout = Add::Ajout(header.getChemin());
           // thread threadAjout(ajout,header.getChemin());
            //threadAjout.join();
            rep = HTTPOK;
            rep = nouvelleAjout.getFile().getTextFull();
        }
    }

    if (write(newsockfd, utils::str::stringToChar(rep), rep.size()) < 0)
    {
        cerr<<"ERROR writing to socket"<<endl;
    }
    else if(verbose)
        cout<<"réponse:"<<endl<<rep<<endl;
    utils::Stats::incRequeteServ(action,header.getChemin());
}


//-------------------getter setter

bool Serveur::getError()
{
    return error;
}


void Serveur::closeSocket()
{
    close(newsockfd);
    close(sockfd);
}


Serveur::~Serveur()
{

}

//----------------------------------------foction de thread pour ajout()

void serv::ajout(string chemin)
{
    if(serv::Serveur::verbose)
        cout<<"[treadAdd]start : "<<chemin<<endl;

    Add::Ajout nouvelleAjout = Add::Ajout(chemin);
    nouvelleAjout.getFile();

    if(serv::Serveur::verbose)
        cout<<"[treadAdd]end"<<endl;
}
