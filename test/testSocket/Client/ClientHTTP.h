#ifndef CLIENTHTTP_H
#define CLIENTHTTP_H
#define BUFFER_SIZE 3000
#define TIMEOUT 2
#include "../defines.h"
#include "../Files/Fichier.h"
#include "../Utils/Url.h"
#include "boost/locale.hpp"
#include <SFML/Network.hpp>

using namespace std;

namespace client
{
    class ClientHTTP
    {
        public:
            ClientHTTP(utils::Url &uri);


    };
}
#endif // CLIENTHTTP_H
