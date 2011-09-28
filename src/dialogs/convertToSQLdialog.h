#ifndef CONVERTTOSQLDIALOG_H
#define CONVERTTOSQLDIALOG_H

#include <QtGui/QDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QSpinBox>
#include <QLabel>
#include <QLineEdit>
#include <QtSql/QSqlDatabase>
#include "core/dbconfig.h"

class QLabel;
class QLineEdit;
class QPushButton;


class convertToSQLdialog : public QDialog
{
    Q_OBJECT

public:
        convertToSQLdialog(QWidget *parent = 0, Qt::WFlags f = Qt::WindowSystemMenuHint);
        virtual ~convertToSQLdialog()
        {}

        dbConfig getDbConfig();
        QSqlDatabase connection();


private:
        QPushButton *button_OK;
        QPushButton *button_NO;
        QPushButton *button_Connect;
        QLineEdit *ui_dbHost;
        QLineEdit *ui_dbPort;
        QLineEdit *ui_dbName;
        QLineEdit *ui_dbUser;
        QLineEdit *ui_dbPass;
        QSpinBox *ui_maxProc;
        QSpinBox *ui_maxSQL;
        QLabel *connect_status;
        QSqlDatabase db;

        bool is_connected;

        dbConfig config;

private slots:
        void make_connect();

};


#endif // CONVERTTOSQLDIALOG_H
