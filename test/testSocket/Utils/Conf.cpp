#include "Conf.h"
using namespace utils;
using namespace std;

map<string,string> Conf::tab;
string Conf::CONFIG_FILE ="findy.conf";

bool* Conf::quitter;

bool Conf::stopCrawl;

void Conf::setQuitter(bool b)
{
    *quitter = b;
}
bool Conf::getQuitter()
{
    return *quitter ;
}



void Conf::load()
{
    //on veut pas quitter on met a false
    bool q=false;
    quitter = &q;
    stopCrawl = false;
    reload();
}


void Conf::reload()
{
    tab.clear();
    ifstream fichierConf(CONFIG_FILE, ios::in);  // on ouvre le fichier conf

    if(fichierConf)//si l'ouverture a réussi
    {
        string previousLine="",actualLine;
        while(!fichierConf.eof()) //jusqu'a la fin du fichier
        {
            getline(fichierConf,actualLine); //on lis ligne par ligne
            if (actualLine != previousLine)
            {
                vector<string> vec = str::split(actualLine,"=");//on split au =
                if(vec.size()==2)
                    tab.insert(make_pair(vec[0],vec[1])); //on insert dans le map
                previousLine=actualLine;
            }
        }
        fichierConf.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;

    cout<<"[conf]lecture du fichier de conf effectué"<<endl;
}


string Conf::getConf(string tabValue)
{
    map<string,string>::iterator it = tab.find(tabValue);//si la valeur est bien dans le tableau

    if(it != tab.end())
        return tab[tabValue];
    else
        cerr << "conf"<<tabValue<<" n'existe pas" << endl;
    throw logic_error("conf inexistant");
    return "";
}




char* Conf::getConfChar(string tabValue) //meme que la précédante mais renvoie un tableau de char
{
    return str::stringToChar(getConf(tabValue));
}




