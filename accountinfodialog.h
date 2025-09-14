#ifndef TRAINDIALOG_H
#define TRAINDIALOG_H

#include <QDialog>
#include "data.h"

namespace Ui {
class AccountInfoDialog;
}

class AccountInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AccountInfoDialog(QWidget *parent = nullptr);
    ~AccountInfoDialog();

public:
    void setData(const AccountInfo& info);

private slots:
    void on_pushButton_clicked();

    void on_checkBoxLoss_stateChanged(int arg);

public:
    AccountInfo info;

private:
    Ui::AccountInfoDialog *ui;
};

#endif
