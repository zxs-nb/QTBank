#ifndef PASSENGERDIALOG_H
#define PASSENGERDIALOG_H

#include <QDialog>
#include "data.h"

namespace Ui {
class RecordInfoDialog;
}

class RecordInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecordInfoDialog(QWidget *parent = nullptr);
    ~RecordInfoDialog();

private slots:
    void on_pushButton_clicked();

public:
    RecordInfo info;

private:
    Ui::RecordInfoDialog *ui;
};

#endif
