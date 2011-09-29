#ifndef DBCONFIG_H
#define DBCONFIG_H

#include <QString>

class dbConfig {
    //переменные для соединения с базой данных
public:
    QString dbHost;
    QString dbPort;
    QString dbName;
    QString dbUser;
    QString dbPass;
    QString tbName;
};

#endif // DBCONFIG_H
