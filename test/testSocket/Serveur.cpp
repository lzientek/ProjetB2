#include "Serveur.h"
#include "Serveur/HttpHeader.h"




using namespace std;

using namespace serv;

bool Serveur::verbose;

Serveur::Serveur()
{
    Serveur(4242);
    sockfd = 0;
    newsockfd = 0;
    portno = 0;
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
    pid_t  pid;


    newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);

    if (read(newsockfd, buffer, BUFFER_SYZE) == -1) //si aucune connection
    {
        //si rien n'est arrivé on attend 0.05sec
        usleep(50000);
    }
    else
    {

        /*  Fork child process to service connection  */

        if ( (pid = fork()) == 0 )
        {

            /*  This is now the forked child process, so
            close listening socket and service request   */

            if ( close(sockfd) < 0 )
                cerr<<"Error closing listening socket in child."<<endl;


            if(verbose)
                cout<<"[serv]envoie rep"<<endl;
            envoieReponse();


            /*  Close connected socket and exit  */

            if ( close(newsockfd) < 0 )
                cerr<<"Error closing connection socket."<<endl;
            exit(EXIT_SUCCESS);

        }


        /*  If we get here, we are still in the parent process,
            so close the connected socket, clean up child processes,
            and go back to accept a new connection.                   */

        if ( close(newsockfd) < 0 )
            cerr<<"Error closing connection socket in parent."<<endl;

        waitpid(-1, NULL, WNOHANG);




    }



    //si aucune erreur on continue l'écoute
    return !error; //TODO : better (exeption)
}



void Serveur::envoieReponse()
{
    HttpHeader header(buffer);

    u_int action = header.getAction();
    string rep = HTTP404;

    if(verbose) //si le mode verbose est activé
        cout<<"[serv]action:"<<endl<<action<<endl;

    if(action != A_404ERROR)
    {
        if(action == A_RECHERCHE) //si l'utilisateur fais une recherche
        {
            Recherche::Resultat resultRecherche = Recherche::Resultat(header.getKeys()); // on passe les arguments de recherche du header a a recherche
            rep = HTTPOK;//on met le header
            rep += resultRecherche.toXml();
            repondre(rep);
        }

        else if( action == A_AJOUT ) //si il veut ajouter une url
        {
            if(verbose)
                cout<<"[serv-add]ajout "<<header.getChemin()<<endl;
            rep = HTTPOK;


            Crawl::SetNextUrl( header.getChemin());

            repondre(rep);

            if(verbose)
                cout<<"[serv-add]ajout terminé"<<endl;


        }
    }
    else
        repondre(rep);


    utils::Stats::incRequeteServ(action,header.getChemin());
}

void Serveur::repondre(string rep)
{
    if (write(newsockfd, utils::str::stringToChar(rep), rep.size()) < 0)
        cerr<<"ERROR writing to socket"<<endl;

    else if(verbose)
        cout<<"[serv]réponse envoye; taille:"<<rep.size()<<endl;
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

