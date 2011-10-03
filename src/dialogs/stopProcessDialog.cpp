#include "dialogs/stopProcessDialog.h"
#include <QDebug>

StopProcessDialog::StopProcessDialog(int maxProc, QWidget *parent, Qt::WFlags f)
    :QDialog(parent, f)
{
    //resize(500, 200);

    QGridLayout *mainLayout = new QGridLayout();

    ok_button = new QPushButton(tr("OK"));
    cancel_button = new QPushButton(tr("Cancel"));

    ok_button->setEnabled(false);


    connect (ok_button, SIGNAL(clicked()), SLOT(accept()));
    connect (cancel_button, SIGNAL(clicked()), SLOT(reject()));

    lb1 = new QLabel(tr("Uloading to MySQL server is in progress"));
    lb1->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(lb1, 0, 0);

    mainLayout->addWidget(ok_button, 3, 2);
    mainLayout->addWidget(cancel_button, 3, 1);

    progressBar = new QProgressBar;
    progressBar->setFormat(tr("%p%"));
    progressBar->setRange(0, 100*maxProc);
    progressBar->setValue(0);
    mainLayout->addWidget(progressBar, 1, 0, 2, 3);

    progress = 0;
    count_unfinished = maxProc;

    setLayout(mainLayout);


}

void StopProcessDialog::inc() {
    progress++;
    progressBar->setValue(progress);
}

void StopProcessDialog::finished() {
    count_unfinished--;
    qDebug() << "Unfinished threads " << count_unfinished;
    if (count_unfinished)
        return;
    ok_button->setEnabled(true);
    cancel_button->setEnabled(false);
    progressBar->setValue(progressBar->maximum());
    lb1->setText(tr("Successfull uploading into MySQL server"));
    emit accepted();
}
