#include "ClientHTTP.h"
using namespace std;
using namespace client;


ClientHTTP::ClientHTTP(utils::Url uri)
{
    urlClient = uri;
    file = "";
    if(urlClient.isValid())
    {
        execute();
    }
    else
        cerr<<"[clientHttp]error url"<<endl<<urlClient.getUri()<<endl;
}



int ClientHTTP::execute()
{
    //recherche dns
        struct hostent * host = gethostbyname(utils::str::stringToChar(urlClient.getUrl()));

        if ( (host == NULL) || (host->h_addr == NULL) )
        {
            cerr << "[ClientHttp]Error retrieving DNS information."<<endl<<urlClient.getUrl() << endl;
            return -1;
        }
        else
        {
            bzero(&client, sizeof(client));
            client.sin_family = AF_INET;
            client.sin_port = htons( 80 );
            memcpy(&client.sin_addr, host->h_addr, host->h_length);


            //creation du socket
            sock = socket(AF_INET, SOCK_STREAM, 0);
            if (sock < 0)
            {

                cerr << "[ClientHttp]Error creating socket." << endl;
                return -1;
            }

            //connection au serveur distant
            if ( connect(sock, (struct sockaddr *)&client, sizeof(client)) < 0 )
            {
                close(sock);
                cerr << "[ClientHttp]Could not connect" << endl;
                 return -1;
            }


            //creation du header
            stringstream ss;
            ss << "GET " << urlClient.getGet() << " HTTP/1.1\r\n"
            << "Host: "<< urlClient.getUrl() <<"\r\n"
            << "Accept: text/html,text/xml, */*\r\n"
            << "\r\n\r\n";
            string request = ss.str();


            if (send(sock, request.c_str(), request.length(), 0) != (int)request.length())
            {
                cerr << "[ClientHttp]Error sending request." << endl;
                return -1;
            }



            char server_reply[BUFFER_SIZE];
            stringstream page;

                int n = 0;
                bool premierTourDeBoucle = true;
                while ((n = recv(sock , server_reply , BUFFER_SIZE , 0))> 0 )
                {
                    page<<server_reply;
                    memset(server_reply,0,BUFFER_SIZE);

                    if(premierTourDeBoucle)
                    {
                        HTTPclientHeader header(page.str());//on parse pour avoir le type
                        if(header.getTypeInt() == F_BINAIRE || header.getHttpCode() > 299 && header.getNewUrl()!="")
                             break;//si c'est un binaire on prend que le header et o break la boucle pour pas tout télécharger

                        premierTourDeBoucle = false ; //pour pas passer a chaque tour

                    }


                }

                file = page.str();

        }
        return 0;
}




ClientHTTP::~ClientHTTP()
{
    //dtor
}
