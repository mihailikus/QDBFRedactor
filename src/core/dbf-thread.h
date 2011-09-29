#ifndef DBFTHREAD_H
#define DBFTHREAD_H

#include <QtGui>
#include "core/mysql_worker.h"
#include "core/dbconfig.h"
#include "core/dbfredactor.h"
//#include "sql.h"
//#include "dbf.h"
//#include "dbfreader.h"

class dbf2sql : public QThread {
Q_OBJECT
private:
    int m_nValue;

    dbConfig mysql;
    DBFRedactor::Header mydbf;
    MySQLWorker *connection;
    int dbfFieldsCount;

    int DataPos;
    int DataForOneProc;
    int ThreadNumber;
    int OnePercent;
    int MaxSQL;
    int CurSQL;

    QString tableListValues;

    char * all_records;

    QChar one_byte; //для экранирования символов, чтоб не объявлять в цикле


    QString sql;    //для хранения SQL-запроса

public:
    dbf2sql(dbConfig sql, DBFRedactor::Header dbf, \
            int ForOneProc, int Number, int one_percent, int maxSQL, \
            QString prepared_string) \
        : m_nValue(10)
    {

        DataPos = Number * ForOneProc;
        DataForOneProc = ForOneProc;
        ThreadNumber = Number;
        //mysql = new dbConfig;
        mysql = sql;
        //mydbf = new DBFRedactor::Header;
        mydbf = dbf;
        OnePercent = one_percent;
        CurSQL = maxSQL;
        MaxSQL = maxSQL;
        dbfFieldsCount = mydbf.recordsCount;
        tableListValues = prepared_string;

    }

    void run()
    {
        qDebug() << "Potok" << ThreadNumber << "thread started";

        connection = new MySQLWorker(mysql, "thread" + \
                                     QString::number(ThreadNumber), MaxSQL);
        qDebug() << "connection created";
        //connection->tbName = mysql->tbName;
        bool ok_connect = connection->db.open();
        if (!ok_connect) {
            return;
        }
        qDebug () << ok_connect;
        sql = "";
        while ( (DataPos < DataForOneProc*(ThreadNumber+1)) \
                && (DataPos < mydbf.recordsCount) \
                && (m_nValue)) {
            qDebug() << "Potok" << ThreadNumber << "in th data pos  = " << DataPos;
            //
            //update_record_signal(DataPos);
            update_one_record(DataPos);


            DataPos++;
            //qDebug() << "Potok" << ThreadNumber << "in th next data pos  = " << DataPos;

        }
        if (sql != "" ) {
            //qDebug() << this->ThreadNumber << " LAST SQL" << sql;
            connection->query(sql);
        }
        connection->db.close();
        emit finished();

        exec();
    }

signals:
    void finished    (   );
    void some_work_done();

private slots:


public slots:
    void update_one_record(int DataPos)
    {
        qDebug() << "Potok" << ThreadNumber <<"update one record started";
        //данные берем из общего массива all_records, куда предварительно считали файл

        //синтаксический разбор полученной строчки из таблицы, учитывая заголовок и тип данных
        if (all_records[DataPos*mydbf.recordLenght] == 32) {
            //qDebug() << "record is not deleted";
        } else {
            qDebug() << "number" << DataPos << "record is DEL";
        }
            int pos = DataPos*mydbf.recordLenght + 1;
            if (CurSQL == MaxSQL) {
                //qDebug() << "-----------------------";
                //qDebug() << sql;
                //qDebug() << "-----------------------";
                connection->query(sql);
                CurSQL = 0;

                sql = "INSERT INTO `" + mysql.dbName + "`.`" + mysql.tbName + "` (";
                sql+= tableListValues;
                sql+= " ) VALUES (";
                qDebug() << "tra-ta-ta" << sql;
            } else {

                sql+=", \n (";
                //qDebug() << "tralivali" << CurSQL;
                CurSQL++;

            }
            DBFRedactor::Field field;

            for (int i = 0; i<dbfFieldsCount; i++) {
                    //qDebug() << this->ThreadNumber << " thread, i=" << i;
                    field = mydbf.fieldsList.at(i);

                    int len = field.firstLenght;

                    QChar ftype = field.textType;
                    QString fstring = "";

                    //все данные хранятся в ASCII-виде
                    //считываем ячейку
                    for (int j=0; j<len; j++)
                    {
                        this->one_byte = QChar::fromAscii(all_records[pos+j]);
                        if (one_byte == '\'' || one_byte == '\\') {
                            fstring += "\\";
                        }
                        fstring += one_byte;
                    }
                    //sql+= "'";

                    switch (ftype.toAscii())
                    {

                    case 'C':
                        //qDebug() << "Line " << fname << " is string";
                        sql += "'" + fstring + "'";
                               //mydbf->codec->toUnicode(fstring.toAscii()) + "'";
                        //sql += "'some data'";
                        //sql += fstring;

                        //qDebug() << fname << fstring << len;
                        break;
                    case 'N':
                        //qDebug() << fname << " is numeric";
                        float value;
                        value = fstring.toFloat();
                        sql+= "'" + fstring + "'";
                        //qDebug() << fname << "=" << value << fstring << len;
                        break;
                    case 'D':
                        //qDebug() << fname << " is date";
                        //DATE_FORMAT('20120311', '%Y%m%d')
                        sql += " DATE_FORMAT ('" + fstring + "', '%Y%m%d') ";
                        //qDebug () << fname << "=" << fdate;
                        break;
                    default:
                        //qDebug() << fname << " is unsupported type";
                        break;
                    }
                    //sql+= "'";
                    //qDebug () << "swich correct";
                    pos += len;
                    if (i<(mydbf.fieldsList.count()-1)) {
                        sql += ", \n";
                    }

                }
                sql += ")";

                qDebug() << "new sql \n" << sql;


            //connection->db.exec(sql);
            //ui_textEdit->append(sql);
            //qDebug() << sql;

            int work = (DataPos-DataForOneProc) % OnePercent;

            if ( !work)
            {
                //sql = "";
                qDebug() << "One more % done";
                emit some_work_done();
            }
/*
        } else {
            //если запись удалена - нафиг ничего не делать
            qDebug() << "Potok" << ThreadNumber << "record is DEL";
        }
*/
        //qDebug () << "Potok" << ThreadNumber << "going up";

    }

    void stop()
    {
        m_nValue = 0;
    }
    /*
    void test(dbfReader* parent)
    {
        qDebug() << parent->NumberOfProc;
    }
    */
};







#endif // DBFTHREAD_H
