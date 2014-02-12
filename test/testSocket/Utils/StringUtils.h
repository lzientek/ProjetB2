#ifndef STRINGUTILS_H_INCLUDED
#define STRINGUTILS_H_INCLUDED
#include <string>
#include <vector>
#include <string.h>

using namespace std;

namespace utils
{
    const string RETOURLIGNE = "\r\n";
    class str
    {
        public:
            static vector<string> split(string str, string sep);
            static char* stringToChar(string str);
            static int calculNote(string text,string motImportant);
    };
}


#endif // STRINGUTILS_H_INCLUDED
