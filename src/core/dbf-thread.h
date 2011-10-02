#ifndef DBFTHREAD_H
#define DBFTHREAD_H

#include <QtGui>
#include <QTableView>
#include "core/mysql_worker.h"
#include "core/dbconfig.h"
#include "core/dbfredactor.h"
#include "dbfredactorpage.h"
//#include "sql.h"
//#include "dbf.h"
//#include "dbfreader.h"

class dbf2sql : public QThread {
Q_OBJECT
private:
    int stopValue;

    dbConfig mysql;
    MySQLWorker *connection;
    QTableView *view;
    DBFRedactorPage *currentPage;
    int dbfFieldsCount;

    int DataPos;
    int DataForOneProc;
    int ThreadNumber;
    int OnePercent;
    int maxSQL;
    int CurSQL;
    QString sql;    //для хранения SQL-запроса
    QString preparedString; //подготовленное начало запроса

public:
    dbf2sql(dbConfig sql, QTableView *curView, DBFRedactorPage *page, \
            int ForOneProc, int Number, int one_percent, int maximumSQL, \
            QString prepared_string) \
        : stopValue(10)
    {

        DataPos = Number * ForOneProc;
        DataForOneProc = ForOneProc;
        ThreadNumber = Number;
        mysql = sql;
        view = curView;
        currentPage = page;
        OnePercent = one_percent;
        CurSQL = maximumSQL;
        maxSQL = maximumSQL;
        preparedString = prepared_string;
    }

    void run()
    {
        qDebug() << "Potok" << ThreadNumber << "thread started";

        connection = new MySQLWorker(mysql, "thread" + \
                                     QString::number(ThreadNumber), maxSQL);
        qDebug() << "connection created";
        //connection->tbName = mysql->tbName;
        bool ok_connect = connection->db.open();
        if (!ok_connect) {
            return;
        }
        qDebug () << ok_connect;

        sql = preparedString;

        QString tempString;
        tempString = "";
        while ( (DataPos < DataForOneProc*(ThreadNumber+1)) \
                && (DataPos < view->model()->rowCount()) \
                && (stopValue)) {
            //qDebug() << "DataPos " << DataPos;
            //qDebug() << "maxSQL " << maxSQL;
            //update one record
            if (!view->isRowHidden(DataPos)){
                //qDebug() <<"curSQL" << CurSQL;

                for (int j = 0; j < view->model()->columnCount(); j++) {
                    //qDebug() << "Thread-" << ThreadNumber <<  " 1j=" << j;
                    const QVariant& value = view->model()->index(DataPos, j).data(Qt::DisplayRole);
                    //qDebug() << "Thread-" << ThreadNumber <<  " 2j=" << j;
                    QString stringValue;

                    switch(currentPage->redactor()->field(view->model()->index(DataPos, j).column()).type) {
                        case DBFRedactor::TYPE_DATE:
                                stringValue = "'" + \
                                        value.toDate().toString("yyyy.MM.dd") +
                                        "'";
                                //qDebug() << "DATE: " << stringValue;
                                break;
                        case DBFRedactor::TYPE_LOGICAL:
                                //qDebug() << "Logical";
                                stringValue = "'" + (value.toBool() ? tr("Yes") : tr("No")) +"'";
                                break;
                        case DBFRedactor::TYPE_CHAR:
                                stringValue = "'" + value.toString() + "'";
                                break;
                        default:
                                //qDebug() << "Default " << j << ", datapos " << DataPos;
                                stringValue = "'" + value.toString() + "'";
                    }
                    if (stringValue == "''")
                        stringValue = "' '";
                    //qDebug() << "Thread-" << ThreadNumber <<  " --2" ;
                    tempString += stringValue;
                    if (j<(view->model()->columnCount()-1)) {
                        tempString += ", ";
                    } else {
                        tempString += ") ";
                    }

                }
                qDebug() << "Thread-" << ThreadNumber <<  " --3";
                DataPos++;
                if (CurSQL == maxSQL) {
                    sql += tempString;
                    tempString ="";
                    //qDebug() << "SQL ============= " << sql;
                    connection->query(sql);
                    CurSQL = 1;

                    sql = preparedString;

                } else {

                    //qDebug() << "temp string == " << tempString;
                    tempString +=", (";
                    CurSQL++;
                }

            }

        }

        if (tempString != "") {

            tempString.remove(tempString.length()-4, 4);
            //qDebug() << "==============" << tempString[0, tempString.length()-2];
            sql+= tempString;
            //qDebug() << "FINISH SQL ============= " << sql;

            connection->query(sql);
        }



        connection->db.close();
        qDebug() << "Potok " << ThreadNumber << " finished";
        emit finished();

        exec();
    }

signals:
    void finished    (   );
    void some_work_done();

private slots:


public slots:

    void stop()
    {
        stopValue = 0;
    }
};







#endif // DBFTHREAD_H
