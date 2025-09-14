#include "accountinfolistwindow.h"
#include "ui_accountinfolistwindow.h"
#include "accountinfodialog.h"
#include "recordinfolistdialog.h"
#include "searchdialog.h"
#include "logindialog.h"
#include <QMessageBox>
#include <QDebug>

AccountInfoListWindow::AccountInfoListWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AccountInfoListWindow)
{
    ui->setupUi(this);
    setWindowTitle("银行储蓄管理系统");
    setTableWidget(ui->tableWidget);

    list.setName("account");
    list.load();

    updateTableWidget(ui->tableWidget, list);
    updateMessage();
}

AccountInfoListWindow::~AccountInfoListWindow()
{
    delete ui;
}

void AccountInfoListWindow::updateTableWidget(QTableWidget *widget, const AccountInfoList &list)
{
    widget->setRowCount(0);
    for(AccountInfo* cursor = list.head; cursor != NULL; cursor = cursor->next) {
        addTableWidget(widget, *cursor);
    }
}

void AccountInfoListWindow::setTableWidget(QTableWidget *widget)
{
    widget->setColumnCount(10);
    QStringList header;
    header << "账号" << "姓名" << "地址" << "储种" << "利率" << "利息(年)" << "余额" << "开户日期" << "是否挂失" << "挂失日期" ;
    widget->setHorizontalHeaderLabels(header);
    widget->setSelectionMode(QAbstractItemView::SingleSelection);
    widget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //不可编辑模式
    widget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //行选定模式
    widget->setSelectionBehavior(QAbstractItemView::SelectRows);
    widget->setColumnWidth(7, 150);
    widget->setColumnWidth(9, 150);
}

void AccountInfoListWindow::addTableWidget(QTableWidget *widget, const AccountInfo &info)
{
    int rowCount = widget->rowCount();
    widget->insertRow(rowCount);
    widget->setItem(rowCount,0,new QTableWidgetItem(info.id));
    widget->setItem(rowCount,1,new QTableWidgetItem(info.name));
    widget->setItem(rowCount,2,new QTableWidgetItem(info.address));
    widget->setItem(rowCount,3,new QTableWidgetItem(info.category));
    widget->setItem(rowCount,4,new QTableWidgetItem(QString("%1%").arg(info.interestRate())));
    widget->setItem(rowCount,5,new QTableWidgetItem(QString::number(info.interest())));
    widget->setItem(rowCount,6,new QTableWidgetItem(QString::number(info.amount)));
    widget->setItem(rowCount,7,new QTableWidgetItem(info.create_date.toString("yyyy/MM/dd#hh:mm:ss")));
    widget->setItem(rowCount,8,new QTableWidgetItem(info.loss ? "是" : "否"));
    if(info.loss) {
        widget->setItem(rowCount,9,new QTableWidgetItem(info.loss_date.toString("yyyy/MM/dd#hh:mm:ss")));
    }
}

void AccountInfoListWindow::on_pushButtonLogin_clicked()
{
    LoginDialog dlg(this);
    if(dlg.exec() == QDialog::Accepted) {
        AccountInfo* info = list.find(dlg.id);
        if(info) {
            if(info->loss==0){
                if(info->password == dlg.password) {
                    AccountInfoDialog dlg(this);
                    dlg.setData(*info);
                    if(dlg.exec() == QDialog::Accepted) {
                        AccountInfo* next = info->next;
                        *info = dlg.info;
                        info->next = next;
                        updateTableWidget(ui->tableWidget, list);
                        updateMessage();
                        list.save();
                        QMessageBox::information(this, "操作提示", "修改成功");
                    }
                } else {
                    QMessageBox::information(this, "操作提示", "密码错误");
                }
            }else{
                QMessageBox::information(this, "操作提示", "该账户已挂失，不允许登录");
            }
        } else {
            QMessageBox::information(this, "操作提示", "没有该账户");
        }
    }
}

void AccountInfoListWindow::on_pushButtonAdd_clicked()
{
    addAccountInfo(ui->tableWidget, list);
}

void AccountInfoListWindow::on_pushButtonDel_clicked()
{
    delAccountInfo(ui->tableWidget, list);
}

void AccountInfoListWindow::on_pushButtonDetails_clicked()
{
    detailsAccountInfo(ui->tableWidget, list);
}

void AccountInfoListWindow::on_pushButtonOpen_clicked()
{
    openAccountInfo(ui->tableWidget, list);
}

void AccountInfoListWindow::on_pushButtonSearch_clicked()
{
    SearchDialog dlg(this);
    QStringList s;
    s << "账号" << "姓名" << "地址" << "余额" << "数量" << "挂失日期" << "开户日期";
    dlg.setSelect(s);
    if(dlg.exec() == QDialog::Accepted){
        while(ui->tableWidget->rowCount()){
            ui->tableWidget->removeRow(0);
        }
        for(AccountInfo* cursor = list.head; cursor != NULL; cursor = cursor->next) {
            if(dlg.select == "账号" && dlg.word == cursor->id){
                addTableWidget(ui->tableWidget, *cursor);
            }
            if(dlg.select == "姓名" && dlg.word == cursor->name){
                addTableWidget(ui->tableWidget, *cursor);
            }
            if(dlg.select == "地址" && dlg.word == cursor->address){
                addTableWidget(ui->tableWidget, *cursor);
            }
            if(dlg.select == "余额" && dlg.word == QString::number(cursor->amount)){
                addTableWidget(ui->tableWidget, *cursor);
            }
            if(dlg.select == "挂失日期" && dlg.word == cursor->loss_date.toString("yyyy/MM/dd")){
                addTableWidget(ui->tableWidget, *cursor);
            }
            if(dlg.select == "开户日期" && dlg.word == cursor->create_date.toString("yyyy/MM/dd")){
                addTableWidget(ui->tableWidget, *cursor);
            }
        }
    }
}

void AccountInfoListWindow::on_pushButtonRefresh_clicked()
{
    updateTableWidget(ui->tableWidget, list);
    updateMessage();
}

void AccountInfoListWindow::addAccountInfo(QTableWidget *widget, AccountInfoList &list)
{
    AccountInfoDialog dlg(this);
    if(dlg.exec() == QDialog::Accepted){
        if(list.add(dlg.info)){
            updateTableWidget(widget, list);
            updateMessage();
            list.save();
            QMessageBox::information(this, "操作提示", "添加成功");
        }else{
            QMessageBox::information(this, "操作提示", "添加失败，存在相同账号");
        }
    }
}

void AccountInfoListWindow::delAccountInfo(QTableWidget *widget, AccountInfoList &list)
{
    QList<QTableWidgetItem*> items = widget->selectedItems();
    int count = items.count();
    if(count > 0){
        if(list.del(items.at(0)->text())){
            list.save();
        }
        updateTableWidget(widget, list);
        updateMessage();
        QMessageBox::information(this, "操作提示", "删除成功");
    }else{
        QMessageBox::information(this, "操作提示", "未选中要操作的数据项");
    }
}

void AccountInfoListWindow::detailsAccountInfo(QTableWidget *widget, AccountInfoList &list)
{
    QList<QTableWidgetItem*> items = widget->selectedItems();
    int count = items.count();
    if(count > 0){
        AccountInfo* info = list.find(items.at(0)->text());
        if(info) {
            AccountInfoDialog dlg(this);
            dlg.setData(*info);
            if(dlg.exec() == QDialog::Accepted){
                *info = dlg.info;
                updateTableWidget(widget, list);
                updateMessage();
                list.save();
                QMessageBox::information(this, "操作提示", "修改成功");
            }
        }
    }else{
        QMessageBox::information(this, "操作提示", "未选中要操作的数据项");
    }
}

void AccountInfoListWindow::openAccountInfo(QTableWidget *widget, AccountInfoList &list)
{
    QList<QTableWidgetItem*> items = widget->selectedItems();
    int count = items.count();
    if(count > 0){
        RecordInfoListDialog dlg(this);
        QString number = items.at(0)->text();
        dlg.setAccount(list.find(number));
        dlg.exec();
        //需要更新账户信息
        if(dlg.ismodify){
            list.save();
            updateTableWidget(widget, list);
            updateMessage();
        }
    }else{
        QMessageBox::information(this, "操作提示", "未选中要操作的数据项");
    }
}

void AccountInfoListWindow::updateMessage()
{
    ui->labelMessage->setText(QString("今后三天到期储备金：%1").arg(countReserve()));
}

double AccountInfoListWindow::countReserve()
{
    double money = 0;
    for(AccountInfo* cursor = list.head; cursor != NULL; cursor = cursor->next) {
        QDateTime datetime;
        if(cursor->category == "定期1年") {
            datetime = cursor->create_date.addYears(1);
        }
        if(cursor->category == "定期3年") {
            datetime = cursor->create_date.addYears(3);
        }
        if(cursor->category == "定期5年") {
            datetime = cursor->create_date.addYears(5);
        }
        QDateTime current = QDateTime::currentDateTime();
        int diff = current.daysTo(datetime);
        if(diff <= 3) {
            money += cursor->amount + cursor->interest();
        }
    }
    return money;
}
