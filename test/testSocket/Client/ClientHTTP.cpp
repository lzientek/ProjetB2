#include "ClientHTTP.h"
using namespace std;
using namespace client;


ClientHTTP::ClientHTTP(utils::Url uri)
{
    urlClient = uri;
    file = "";
    if(urlClient.getUrl()!="") //si c'est un url valide
    {
        //recherche dns
        struct hostent * host = gethostbyname(utils::str::stringToChar(urlClient.getUrl()));

        if ( (host == NULL) || (host->h_addr == NULL) )
            cerr << "[ClientHttp]Error retrieving DNS information."<<endl<<urlClient.getUrl() << endl;


        bzero(&client, sizeof(client));
        client.sin_family = AF_INET;
        client.sin_port = htons( 80 );
        memcpy(&client.sin_addr, host->h_addr, host->h_length);


        //creation du socket
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0)
            cerr << "[ClientHttp]Error creating socket." << endl;


        //connection au serveur distant
        if ( connect(sock, (struct sockaddr *)&client, sizeof(client)) < 0 )
        {
            close(sock);
            cerr << "[ClientHttp]Could not connect" << endl;
        }

        //creation du header
        stringstream ss;
        ss << "GET " << urlClient.getGet() << " HTTP/1.1\r\n"
        << "Host: "<< urlClient.getUrl() <<"\r\n"
        << "Accept: text/html,text/xml, */*\r\n"
        << "\r\n\r\n";
        string request = ss.str();


        if (send(sock, request.c_str(), request.length(), 0) != (int)request.length())
            cerr << "[ClientHttp]Error sending request." << endl;

        //TODO : faire quelque chose de potable qui fonctionne
        char server_reply[2000];
        stringstream page;
        int n = 0;
        while ((n = recv(sock , server_reply , 2000 , 0))> 0 )
        {
            page<< server_reply;
        }
        file = page.str();
    }
    else
        cerr<<"[clientHttp]error url"<<endl<<urlClient.getUri()<<endl;
}








ClientHTTP::~ClientHTTP()
{
    //dtor
}
