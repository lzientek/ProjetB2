#ifndef SERVEUR_H
#define SERVEUR_H
#include "defines.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/fcntl.h>
#include <string.h>
#include "Serveur/HttpHeader.h"
#include "Recherche/Resultat.h"
#include "Files/Fichier.h"
#include "Utils/Stats.h"
#include "ajout/Ajout.h"
#define BUFFER_SYZE 6000

namespace serv
{
    const string HTTPOK = "HTTP/1.1 200 OK\r\n\r\n";
    const string HTTP404 = "HTTP/1.1 404 Not Found\r\n\r\n";

    class Serveur
    {
        public:
            Serveur();
            Serveur(int port);
            virtual ~Serveur();
            bool ecoute();
            void envoieReponse();
            bool getError();
            void closeSocket();
            static bool verbose;
        protected:
        private:
            bool error;
            int sockfd, newsockfd, portno;
            struct sockaddr_in serv_addr, cli_addr;
            char buffer[BUFFER_SYZE];
            socklen_t clilen;
    };

}
#endif // SERVEUR_H
