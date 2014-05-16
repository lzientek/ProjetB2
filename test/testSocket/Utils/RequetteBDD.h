#ifndef REQUETTEBDD_H
#define REQUETTEBDD_H

#include "Conf.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "mysql_connection.h"
#include "mysql_driver.h"
#include "../Files/Fichier.h"
#include "Algo.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <cppconn/prepared_statement.h>

using namespace std;

namespace utils
{

    class RequetteBDD
    {
        public:
            RequetteBDD(string query="");
            virtual ~RequetteBDD();
            sql::ResultSet* executeSQL(string query);
            void add(vector<string> urls);
            void add(Files::Fichier file);
            void update(Files::Fichier file,string url,int temps=0);
            bool verifUrl(string url);
            vector<Files::Fichier> search(vector<string> words,int debut=0,int nombre=0);
            string oldestCrawl();

        private:
            string like(string word);
            sql::mysql::MySQL_Driver *driver;
            sql::Connection *con;
            sql::Statement *stmt;
    };


    class DataBuf : public streambuf
    {
        public:
            DataBuf(char * d, size_t s)
            {
                setg(d, d, d + s);
            }
    };
}
#endif // REQUETTEBDD_H
