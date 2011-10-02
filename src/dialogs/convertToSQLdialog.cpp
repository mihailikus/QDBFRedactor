#include <QDebug>
#include "src/dialogs/convertToSQLdialog.h"


convertToSQLdialog::convertToSQLdialog (QWidget *parent, Qt::WFlags f) {
    this->resize(600, 200);
    is_connected = false;

    QGridLayout *mainLayout = new QGridLayout();

    button_OK = new QPushButton(tr("Convert"));
    button_NO = new QPushButton(tr("Cancel"));

    button_OK->setEnabled(false);

    connect (button_OK, SIGNAL(clicked()), SLOT(accept()));
    connect (button_NO, SIGNAL(clicked()), SLOT(reject()));

    mainLayout->addWidget(button_OK, 0, 5);
    mainLayout->addWidget(button_NO, 1, 5);

    QLabel *lb1 = new QLabel(tr("DB host"));
    QLabel *lb2 = new QLabel(tr("DB port"));
    QLabel *lb3 = new QLabel(tr("DB name"));
    QLabel *lb4 = new QLabel(tr("DB user"));
    QLabel *lb5 = new QLabel(tr("DB pass"));

    mainLayout->addWidget(lb1, 0, 0);
    mainLayout->addWidget(lb2, 0, 2);
    mainLayout->addWidget(lb3, 1, 0);
    mainLayout->addWidget(lb4, 2, 0);
    mainLayout->addWidget(lb5, 2, 2);

    ui_dbHost = new QLineEdit("localhost");
    ui_dbPort = new QLineEdit();
    ui_dbName = new QLineEdit("music");
    ui_dbUser = new QLineEdit("music");
    ui_dbPass = new QLineEdit("tralivali");

    mainLayout->addWidget(ui_dbHost, 0, 1);
    mainLayout->addWidget(ui_dbPort, 0, 3);
    mainLayout->addWidget(ui_dbName, 1, 1);
    mainLayout->addWidget(ui_dbUser, 2, 1);
    mainLayout->addWidget(ui_dbPass, 2, 3);

    button_Connect = new QPushButton (tr("Connect"));
    mainLayout->addWidget(button_Connect, 3, 0);
    connect(button_Connect, SIGNAL(clicked()), SLOT(make_connect()));

    connect_status = new QLabel(tr("Status: not connected"));
    mainLayout->addWidget(connect_status, 3, 2, 1, 2);

    QLabel *lb7 = new QLabel(tr("Max proc"));
    QLabel *lb8 = new QLabel(tr("Max SQL"));
    mainLayout->addWidget(lb7, 4, 0);
    mainLayout->addWidget(lb8, 4, 2);

    //maxProc & maxSQL - for multi-threading
    ui_maxProc = new QSpinBox();
    ui_maxSQL = new QSpinBox();
    mainLayout->addWidget(ui_maxProc, 4, 1);
    mainLayout->addWidget(ui_maxSQL, 4, 3);
    ui_maxProc->setMinimum(1);
    ui_maxProc->setMaximum(50); //it is fixed value for create threads
    ui_maxSQL->setMinimum(1);
    ui_maxSQL->setMaximum(1000);
    ui_maxSQL->setValue(3);
    ui_maxProc->setValue(1);


    setLayout(mainLayout);

}

void convertToSQLdialog::make_connect() {
    qDebug() << "connectingn to MySQL";

    config = getDbConfig();

    db = QSqlDatabase::addDatabase("QMYSQL", "connectionFromReader");

    db.setHostName(config.dbHost);
    if (config.dbPort != "" ) {
        db.setPort(config.dbPort.toInt());
    }
    db.setDatabaseName(config.dbName);
    db.setUserName(config.dbUser);
    db.setPassword(config.dbPass);

    if (db.open()) {
        connect_status->setText(tr("Status: connected"));
        button_OK->setEnabled(true);
        is_connected = true;
    }

}

QSqlDatabase convertToSQLdialog::connection() {
    if (!is_connected) {
        make_connect();
    }
    return db;
}

dbConfig convertToSQLdialog::getDbConfig() {
    dbConfig conf;
    conf.dbHost = ui_dbHost->text();
    conf.dbPort = ui_dbPort->text();
    conf.dbName = ui_dbName->text();
    conf.dbUser = ui_dbUser->text();
    conf.dbPass = ui_dbPass->text();
    return conf;
}


int convertToSQLdialog::get_number_proc() {
    return ui_maxProc->value();
}

int convertToSQLdialog::get_max_sql() {
    return ui_maxSQL->value();
}
