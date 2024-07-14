#include "sql.h"

SQL::SQL(QHostAddress adress,quint16 p)
{
    this->serverAdress=adress;
    this->dbp=p;
    this->db->connectToHost(serverAdress,dbp);
    if(db->waitForConnected())
    {

    }
}
