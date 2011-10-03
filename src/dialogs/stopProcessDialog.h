#ifndef STOPPROCESSDIALOG_H
#define STOPPROCESSDIALOG_H

#include <QtGui/QDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QProgressBar>
#include <QLabel>

class QLabel;
class QPushButton;
class QProgressBar;

class StopProcessDialog : public QDialog {
    Q_OBJECT

public:
    StopProcessDialog(int maxProc, QWidget *parent = 0, Qt::WFlags f = Qt::WindowSystemMenuHint);
    virtual ~StopProcessDialog()
    {}

private:
    QProgressBar *progressBar;
    QLabel *lb1;
    QGridLayout *mainLayout;
    QPushButton *ok_button, *cancel_button;
    int progress;
    int count_unfinished;

public slots:
    void inc();
    void finished();


};


#endif // STOPPROCESSDIALOG_H
