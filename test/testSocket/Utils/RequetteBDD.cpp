#include "RequetteBDD.h"
using namespace utils;
using namespace std;

RequetteBDD::RequetteBDD(string query)
{
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect(Conf::getConf("adresseMysql"), Conf::getConf("userMysql"), Conf::getConf("mdpMysql"));//connection au serveur
    stmt = con->createStatement();
    stmt->execute("USE "+ Conf::getConf("BDDname")); //selection de la bdd
    if(query!="")
    {
        executeSQL(query);
    }
}

vector<Files::Fichier> RequetteBDD::search(vector<string> words,int debut,int nombre)
{
    ostringstream query;
    query <<"SELECT * FROM files WHERE ";
    for(unsigned i = 0; i < words.size(); i++)
        query<< "url "<<like(words[i])<<" OR motImportant "<<like(words[i])<< "OR txt "<<like(words[i]);
    query << " LIMIT " << debut <<","<< nombre;

    sql::ResultSet  *result;
    result = executeSQL(query);

    vector<Files::Fichier> resultTab;

    while (res->next())
    {

         resultTab.insert(resultTab.end(), Files::Fichier( result->getString("titre"),
                                                           result->getString("url"),
                                                           result->getString("txt").substr(1,200),
                                                           result->getInt("type"),
                                                          utils::str::calculNote(result->getString("txt"),
                                                                                 result->getString("motImportant"))
                                                           ) );
    }

    delete result;
    return resultTab;
    }

    string RequetteBDD::like(string word)
{
    return "LIKE %"+word+"%";
}

sql::ResultSet* RequetteBDD::executeSQL(string query)
{
    return stmt->execute(query);
}

RequetteBDD::~RequetteBDD()
{
    delete stmt;
    delete con;
}
