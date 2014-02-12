#ifndef URL_H
#define URL_H
#include <iostream>
#include <string>

using namespace std;


namespace utils
{
    class Url
    {
        public:
            Url(string uri="");
            string getUrl(){return url;}
            string getGet(){return get;}
            string getUri(){return uri;}
            bool isValid(){return (get!="" && url!="");}
            virtual ~Url();
        protected:
        private:
            void parse();
            string uri;
            string url;
            string get;

    };
}

#endif // URL_H
