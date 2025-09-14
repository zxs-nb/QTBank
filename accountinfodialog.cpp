#include "accountinfodialog.h"
#include "ui_accountinfodialog.h"
#include <QDate>

AccountInfoDialog::AccountInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountInfoDialog)
{
    ui->setupUi(this);
    setWindowTitle("账户信息");
    //价格只允许浮点数
    ui->lineEditAmount->setValidator(new QDoubleValidator(this));
    ui->lineEditAmount->setText("0.00");
    ui->lineEditAmount->setReadOnly(true);
    ui->dateTimeEditCreate->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEditCreate->setCalendarPopup(true);
    ui->dateTimeEditCreate->setReadOnly(true);
    ui->dateTimeEditLoss->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEditLoss->setCalendarPopup(true);
    QStringList category;
    category << "定期1年" << "定期3年" << "定期5年";
    ui->comboBoxCategory->addItems(category);
    on_checkBoxLoss_stateChanged(ui->checkBoxLoss->isChecked());
}

AccountInfoDialog::~AccountInfoDialog()
{
    delete ui;
}

void AccountInfoDialog::setData(const AccountInfo &info)
{
    ui->lineEditID->setReadOnly(true);
    ui->lineEditID->setText(info.id);
    ui->lineEditName->setText(info.name);
    ui->lineEditPassword->setText(info.password);
    ui->lineEditAddress->setText(info.address);
    ui->lineEditAmount->setText(QString("%1").arg(info.amount));
    ui->comboBoxCategory->setCurrentText(info.category);
    ui->checkBoxLoss->setChecked(info.loss ? true : false);
    ui->dateTimeEditLoss->setDateTime(info.loss_date);
    ui->dateTimeEditCreate->setDateTime(info.create_date);
}

void AccountInfoDialog::on_pushButton_clicked()
{
    info.id = ui->lineEditID->text().trimmed().replace(QRegExp("\\s"), "");
    if(info.id.isEmpty()) return;
    info.name = ui->lineEditName->text().trimmed().replace(QRegExp("\\s"), "");
    if(info.name.isEmpty()) return;
    info.password = ui->lineEditPassword->text().trimmed().replace(QRegExp("\\s"), "");
    if(info.password.isEmpty()) return;
    info.address = ui->lineEditAddress->text().trimmed().replace(QRegExp("\\s"), "");
    if(info.address.isEmpty()) return;
    QString amount = ui->lineEditAmount->text().trimmed().replace(QRegExp("\\s"), "");
    if(amount.isEmpty()) return;
    info.amount = amount.toDouble();
    info.category = ui->comboBoxCategory->currentText().trimmed().replace(QRegExp("\\s"), "");;
    if(info.category.isEmpty()) return;
    info.create_date = ui->dateTimeEditCreate->dateTime();
    info.loss = ui->checkBoxLoss->isChecked() ? 1 : 0;
    if(info.loss) {
        info.loss_date = ui->dateTimeEditLoss->dateTime();
    }
    accept();
}

void AccountInfoDialog::on_checkBoxLoss_stateChanged(int arg)
{
    if(arg) {
        ui->dateTimeEditLoss->setVisible(true);
    }else{
        ui->dateTimeEditLoss->setVisible(false);
    }
}
