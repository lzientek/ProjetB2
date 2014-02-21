#ifndef CLIENTHTTP_H
#define CLIENTHTTP_H
#define BUFFER_SIZE 3000
#include "../defines.h"
#include "../Files/Fichier.h"
#include "../Utils/Url.h"

using namespace std;
namespace client
{
    class ClientHTTP
    {
        public:
            ClientHTTP(utils::Url uri);

            string getResultStr(){return file;}
            virtual ~ClientHTTP();
        protected:
        private:
            utils::Url urlClient;
            int execute();
            string file;
            struct sockaddr_in client;
            int sock;
    };
}
#endif // CLIENTHTTP_H
