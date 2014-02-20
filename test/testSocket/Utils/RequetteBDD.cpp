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
    ostringstream query("");
    query <<"SELECT * FROM files WHERE ";
    for(unsigned i = 0; i < words.size(); i++)
    {
        if(i>0)
            query<<"OR ";
        query<< "url "<<like(words[i])<<" OR motImportant "<<like(words[i])<< " OR txt "<<like(words[i])<<" ";
    }

    query << "LIMIT " << debut <<","<< nombre;

    sql::ResultSet  *result;

    result = executeSQL(query.str());

    vector<Files::Fichier> resultTab;

    while (result->next())
    {

        resultTab.insert(resultTab.end(), Files::Fichier( result->getString("titre"),
                         result->getString("url"),
                         result->getString("motImportant"),
                         result->getInt("type"),
                         utils::str::calculNote(result->getString("txt"),
                                                result->getString("motImportant"))
                                                        )
                        );
    }

    result->close();

    delete result;
    return resultTab;
}



utils::Url RequetteBDD::oldestCrawl(int &id) //crawl le plus ancien
{

    string query("SELECT id,url FROM files ORDER BY lastcrawl ASC LIMIT 1 ");

    sql::ResultSet  *result;

    result = executeSQL(query);


    result->next();

    utils::Url urlToReturn("http://" + result->getString("url"));
    id = result->getInt("id");
    result->close();

    delete result;
    return urlToReturn;
}



void RequetteBDD::add(Files::Fichier file)
{

    string query = "INSERT INTO files(titre,url,type,txt,motImportant,lastcrawl) VALUES (?,?,?,?,?,?) ";

    sql::PreparedStatement  *prep_stmt;

    prep_stmt = con->prepareStatement(query);

    prep_stmt->setString(1,file.getNom()); //titre
    prep_stmt->setString(2,file.getURL().getUri()); //url
    prep_stmt->setInt(3,file.getTypeInt()); //type
    prep_stmt->setString(4,file.getTextFull()); //txt
    prep_stmt->setString(5,str::generateMotImportant(file.getTextFull())); //mot important
    prep_stmt->setInt(6,time(NULL)); //timstamp

    prep_stmt->execute();
    delete prep_stmt;

}




void RequetteBDD::update(int id,Files::Fichier file)
{
    if(id>=0 && !file.isEmpty())
    {

        string query = "UPDATE files SET titre=?,url=?,type=?,txt=?,motImportant=?,lastcrawl=? WHERE id=? ";

        sql::PreparedStatement  *prep_stmt;

        prep_stmt = con->prepareStatement(query);

        prep_stmt->setString(1,file.getNom()); //titre
        prep_stmt->setString(2,file.getURL().getUri()); //url
        prep_stmt->setInt(3,file.getTypeInt()); //type
        prep_stmt->setString(4,file.getTextFull()); //txt
        prep_stmt->setString(5,str::generateMotImportant(file.getTextFull())); //mot important
        prep_stmt->setInt(6,time(NULL)); //timstamp
        prep_stmt->setInt(7,id); //where ID

        prep_stmt->execute();
        delete prep_stmt;
    }

}



string RequetteBDD::like(string word)
{
    return "LIKE '%"+word+"%'";
}

sql::ResultSet* RequetteBDD::executeSQL(string query)
{
    return stmt->executeQuery(query);
}

RequetteBDD::~RequetteBDD()
{
    delete stmt;
    delete con;
}
