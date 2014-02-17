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

    cout<<query.str()<<endl;


    result = executeSQL(query.str());

    vector<Files::Fichier> resultTab;

    while (result->next())
    {

        resultTab.insert(resultTab.end(), Files::Fichier( result->getString("titre"),
                         result->getString("url"),
                         result->getString("motImportant").substr(0,200),
                         result->getInt("type"),
                         utils::str::calculNote(result->getString("txt"),
                                                result->getString("motImportant"))
                                                        ) );
    }
    cout<<"rowsCoutn"<<result->rowsCount()<<endl;
    result->close();

    delete result;
    return resultTab;
}


void RequetteBDD::add(Files::Fichier file)
{

    string query = "INSERT INTO files(titre,url,type,txt,motImportant,lastcrawl) VALUES (?,?,?,?,?,?) ";

    sql::PreparedStatement  *prep_stmt;

    prep_stmt = con->prepareStatement(query);

    prep_stmt->setString(1,file.getNom());
    prep_stmt->setString(2,file.getURL());
    prep_stmt->setInt(3,file.getTypeInt());
    prep_stmt->setString(4,file.getTextFull());
    prep_stmt->setString(5,str::generateMotImportant(file.getTextFull()));
    prep_stmt->setInt(6,time(NULL));

    prep_stmt->execute();
    delete prep_stmt;

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
