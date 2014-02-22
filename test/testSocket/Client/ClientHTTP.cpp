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
        cerr<<"[clientHttp]error url :"<<uri.getUri()<<endl;
}



int ClientHTTP::execute() //comme ca on fait des return pour bloquer la suite de l'execution du prog
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

        int n = 0,totalsize=0;
        bool premierTourDeBoucle = true;


        struct timeval begin , now;
        double timediff;

        //make socket non blocking
        fcntl(sock, F_SETFL, O_NONBLOCK);

        //beginning time
        gettimeofday(&begin , NULL);


        while ( 1 )
        {
            gettimeofday(&now , NULL);

            //temps écoulé en seconde
            timediff = (now.tv_sec - begin.tv_sec) + 1e-6 * (now.tv_usec - begin.tv_usec);
            //sion a u des donner on attend le timeout pour break
            if( totalsize > 0 && timediff > TIMEOUT )
            {
                break;
            }
            //si on a rien recu on atten un peu plus longtemps
            else if( timediff > TIMEOUT*2)
            {
                break;
            }

            memset(server_reply,0,BUFFER_SIZE);


            if( (n = recv(sock , server_reply , BUFFER_SIZE , 0))> 0)
            {
                cout<<n<<endl;
                file+=string(server_reply);
                totalsize+=n;

                if(premierTourDeBoucle)
                {
                    string head = file;
                    unsigned pos;
                    if((pos = head.find("Content-Type: ")) != string::npos )
                        if(head.substr(pos,10).find("text")!=string::npos )
                            break; //si c'est un binaire

                    premierTourDeBoucle = false ; //pour pas passer a chaque tour

                }

                //reset du temps
                gettimeofday(&begin , NULL);
            }
            else
            {
                //si rien n'est arrivé on attend 0.05sec
                usleep(50000);
            }


        }
    }
    return 0;
}




ClientHTTP::~ClientHTTP()
{
    //dtor
}
