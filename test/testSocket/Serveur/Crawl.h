#ifndef CRAWL_H
#define CRAWL_H
#include <iostream>
#include "../Utils/Conf.h"
#include "../Utils/RequetteBDD.h"
#include "../ajout/Ajout.h"
#include "../Utils/Conf.h"


namespace serv
{

class Crawl
{
public:
    static std::string GetNextUrl();
    static void SetNextUrl(std::string url);
    Crawl();
    void next();
    virtual ~Crawl();
protected:
private:
    int actualId;

};

}
#endif // CRAWL_H
