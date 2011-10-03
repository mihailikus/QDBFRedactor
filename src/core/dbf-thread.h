#ifndef DBFTHREAD_H
#define DBFTHREAD_H

#include <QtGui>
//#include <QTableView>
#include "core/mysql_worker.h"
#include "core/dbconfig.h"
#include "core/dbfredactor.h"
//#include "dbfredactorpage.h"
//#include "sql.h"
//#include "dbf.h"
//#include "dbfreader.h"

class dbf2sql : public QThread {
Q_OBJECT
private:
    int stopValue;

    dbConfig mysql;
    MySQLWorker *connection;
    //QTableView *view;
    QList<DBFRedactor::Field> fields;
    int rowCount;
    int columnCount;
    QStringList records;
    //DBFRedactorPage *currentPage;
    int dbfFieldsCount;

    int DataPos;
    int RowPos;
    int DataForOneProc;
    int ThreadNumber;
    int OnePercent;
    int maxSQL;
    int CurSQL;
    QString sql;    //для хранения SQL-запроса
    QString preparedString; //подготовленное начало запроса

    QString tempString;
    QString stringValue;



public:
    dbf2sql(dbConfig sql, QStringList all_records, int rows, int cols,
            QList<DBFRedactor::Field> header_fields,
            int ForOneProc, int Number, int one_percent, int maximumSQL, \
            QString prepared_string) \
        : stopValue(10)
    {

        DataPos = Number * ForOneProc;
        DataForOneProc = ForOneProc;
        ThreadNumber = Number;
        mysql = sql;
        //view = curView;
        records = all_records;
        rowCount = rows;
        columnCount = cols;
        fields = header_fields;
        RowPos = DataPos*columnCount;

        //currentPage = page;
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

        tempString = "";
        while ( (DataPos < DataForOneProc*(ThreadNumber+1)) \
                && (DataPos < rowCount) \
                && (stopValue)) {
            //qDebug() << "DataPos " << DataPos;
            //qDebug() << "maxSQL " << maxSQL;
            //update one record
            //if (!view->isRowHidden(DataPos)){
            if (stopValue) {
                //qDebug() << "DataPos is " << DataPos;
                for (int j = 0; j < columnCount; j++) {
                    //qDebug() << "Thread-" << ThreadNumber <<  " 1j=" << j;
                    //qDebug() << "Thread-" << ThreadNumber <<  " 2j=" << j;
                    make_one_record(j);

                    if (stringValue == "''")
                        stringValue = "' '";
                    //qDebug() << "Thread-" << ThreadNumber <<  " --2" ;
                    tempString += stringValue;
                    if (j<(columnCount-1)) {
                        tempString += ", ";
                    } else {
                        tempString += ") ";
                    }

                }

                //qDebug() << "Thread-" << ThreadNumber <<  " --3";
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
            DataPos++;
            RowPos += columnCount;

            int work = (DataPos-DataForOneProc) % OnePercent;
            if ( !work)
            {
                emit some_work_done();
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

    void make_one_record(int j) {
        //qDebug() <<"curSQL" << CurSQL;
        //const QVariant& value = view->model()->index(DataPos, j).data(Qt::DisplayRole);
        //const QString value = view->model()->index(DataPos, j).data().toString();
        QString value = records.at(RowPos + j);
        //const QVariant& value("some text");
        //qDebug() << "value is " << value;


        switch(fields.at(j).type) {
            case DBFRedactor::TYPE_DATE:
                    stringValue = "'" + \
                            //value.toDate().toString("yyyy.MM.dd") +
                            value +
                            "'";
                    //qDebug() << "DATE: " << stringValue;
                    break;
            case DBFRedactor::TYPE_LOGICAL:
                    //qDebug() << "Logical";
                    stringValue = "'" +
                            //(value.toBool() ? tr("Yes") : tr("No"))
                            value
                            +"'";
                    break;
            case DBFRedactor::TYPE_CHAR:
                    value.replace('\\', "\\\\");
                    value.replace('\'', "\\\'");
                    stringValue = "'" +
                            //value.toString()
                            value
                            + "'";
                    break;
            default:
                    //qDebug() << "Default " << j << ", datapos " << DataPos;
                    stringValue = "'" +
                            //value.toString()
                            value
                            + "'";
        }


    }
};

#endif // DBFTHREAD_H
