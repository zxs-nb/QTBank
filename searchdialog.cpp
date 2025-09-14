#include "searchdialog.h"
#include "ui_searchdialog.h"

SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
    setWindowTitle("查询");
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::setSelect(const QStringList &list)
{
    ui->comboBox->addItems(list);
    ui->comboBox->setCurrentIndex(0);
}

void SearchDialog::on_pushButton_clicked()
{
    word = ui->lineEdit->text().trimmed();
    if(word.isEmpty()) return;
    select = ui->comboBox->currentText();
    accept();
}
