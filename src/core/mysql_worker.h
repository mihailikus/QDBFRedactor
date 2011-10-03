#ifndef MYSQL_WORKER_H
#define MYSQL_WORKER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QSqlQuery>
#include "core/dbconfig.h"

class MySQLWorker : public dbConfig, public QSqlDatabase {
public:
    QString tableListValues;    //rows for insert-sql-query (already formatted)
    QString sql;
    //QString tbName;
    QSqlDatabase db;
    int NumberOfMaxSQL;
    int CurrentSQL;

    MySQLWorker(dbConfig config, QString connectionName, int maxSQL) {
        this->db = QSqlDatabase::addDatabase("QMYSQL", connectionName);
        db.setHostName(config.dbHost);
        if (config.dbPort != "" ) {
            db.setPort(config.dbPort.toInt());
        }
        db.setDatabaseName(config.dbName);
        db.setUserName(config.dbUser);
        db.setPassword(config.dbPass);
        NumberOfMaxSQL = maxSQL;
        CurrentSQL = maxSQL;
        db.open();
    }

    bool query (QString sql="") {
        QString qr;
        if (sql=="") {
            qr = this->sql;
        } else {
            qr = sql;
        }
        db.exec(qr);
        if (db.lastError().text() == " ") {
            return false;
        } else {
            qDebug() << "Error in SQL " << this->db.lastError().text();
            qDebug() << "QUERY is =================" << qr << "=============";
            return true;
        }
    }

};


#endif // MYSQL_WORKER_H
