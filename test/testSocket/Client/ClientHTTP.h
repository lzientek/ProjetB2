#ifndef CLIENTHTTP_H
#define CLIENTHTTP_H
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
            Files::Fichier getResultFile();
            string getResultStr()
            {
                return file;
            }
            virtual ~ClientHTTP();
        protected:
        private:
            utils::Url urlClient;
            Files::Fichier resultFile;
            string file;
            struct sockaddr_in client;
            int sock;
    };
}
#endif // CLIENTHTTP_H
