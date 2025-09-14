#include "recordinfodialog.h"
#include "ui_recordinfodialog.h"

RecordInfoDialog::RecordInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordInfoDialog)
{
    ui->setupUi(this);
    setWindowTitle("业务信息");
    QStringList list;
    list << "存款" << "取款";
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit->setReadOnly(true);
    ui->comboBox->addItems(list);
    ui->comboBox->setCurrentIndex(0);
    ui->dateTimeEdit->setCalendarPopup(true);
    //金额只允许浮点数
    ui->lineEditAmount->setValidator(new QDoubleValidator(this));
}

RecordInfoDialog::~RecordInfoDialog()
{
    delete ui;
}

void RecordInfoDialog::on_pushButton_clicked()
{
    info.date = ui->dateTimeEdit->dateTime();
    QString amount = ui->lineEditAmount->text().trimmed();
    if(amount.isEmpty())return;
    info.amount = amount.toDouble();
    if(info.amount == 0.0) return;
    info.job_number = ui->lineEditJobNumber->text().trimmed().replace(QRegExp("\\s"), "");
    if(info.job_number.isEmpty()) return;
    info.type = ui->comboBox->currentText();
    if(info.type.isEmpty()) return;
    accept();
}
