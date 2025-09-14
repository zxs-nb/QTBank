#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_clicked()
{
    id = ui->lineEditID->text().trimmed().replace(QRegExp("\\s"), "");
    password = ui->lineEditPassword->text().trimmed().replace(QRegExp("\\s"), "");
    if(id.isEmpty()) return;
    if(password.isEmpty()) return;
    accept();
}
