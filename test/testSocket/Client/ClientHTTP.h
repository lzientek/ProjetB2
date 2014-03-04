#ifndef CLIENTHTTP_H
#define CLIENTHTTP_H
#define BUFFER_SIZE 3000
#define TIMEOUT 2
#include "../defines.h"
#include "../Files/Fichier.h"
#include "../Utils/Url.h"
#include "boost/locale.hpp"

using namespace std;
namespace client
{
    class ClientHTTP
    {
        public:
            ClientHTTP(utils::Url &uri,string cookies ="");

            string getResultStr(){return file;}
            virtual ~ClientHTTP();
        protected:
        private:
            utils::Url urlClient;
            int execute();
            string file;
            string cookies;
            struct sockaddr_in client;
            int sock;
    };
}
#endif // CLIENTHTTP_H
