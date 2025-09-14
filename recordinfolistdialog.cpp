#include "recordinfolistdialog.h"
#include "ui_recordinfolistdialog.h"
#include "recordinfodialog.h"
#include "searchdialog.h"
#include <QMessageBox>

RecordInfoListDialog::RecordInfoListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordInfoListDialog),
    info(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("存取款业务办理");
     ismodify = false;
    setTableWidget(ui->tableWidget);
}

RecordInfoListDialog::~RecordInfoListDialog()
{
    delete ui;
}

void RecordInfoListDialog::setAccount(AccountInfo* info)
{
    this->info = info;
    list.setName(this->info->id);
    list.load();
    on_pushButtonRefresh_clicked();
}

void RecordInfoListDialog::updateTableWidget(QTableWidget *widget, const RecordInfoList &list)
{
    widget->setRowCount(0);
    for(auto& item : list.data) {
        addTableWidget(widget, item);
    }
}

void RecordInfoListDialog::setTableWidget(QTableWidget *widget)
{
    widget->setColumnCount(4);
    QStringList header;
    header << "日期" << "营业员工号" << "业务类型" << "金额";
    widget->setHorizontalHeaderLabels(header);
    widget->setSelectionMode(QAbstractItemView::SingleSelection);
    widget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //不可编辑模式
    widget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //行选定模式
    widget->setSelectionBehavior(QAbstractItemView::SelectRows);
    widget->setColumnWidth(0, 150);
}

void RecordInfoListDialog::addTableWidget(QTableWidget *widget, const RecordInfo &info)
{
    int rowCount = widget->rowCount();
    widget->insertRow(rowCount);
    widget->setItem(rowCount,0,new QTableWidgetItem(info.date.toString("yyyy/MM/dd#hh:mm:ss")));
    widget->setItem(rowCount,1,new QTableWidgetItem(info.job_number));
    widget->setItem(rowCount,2,new QTableWidgetItem(info.type));
    widget->setItem(rowCount,3,new QTableWidgetItem(QString::number(info.amount)));
}

void RecordInfoListDialog::on_pushButtonAdd_clicked()
{
    RecordInfoDialog dlg(this);
    if(dlg.exec() == QDialog::Accepted){
        if(dlg.info.type == "存款") {
            info->amount += dlg.info.amount;
            list.add(dlg.info);
            list.save();
            updateTableWidget(ui->tableWidget, list);
             ismodify = true;
        }else{
            if(dlg.info.amount <= info->amount) {
                info->amount -= dlg.info.amount;
                list.add(dlg.info);
                list.save();
                updateTableWidget(ui->tableWidget, list);
                 ismodify = true;
            } else {
                QMessageBox::information(this, "操作提示", "余额不足");
            }
        }
    }
}

void RecordInfoListDialog::on_pushButtonDel_clicked()
{
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    int count = items.count();
    if(count > 0){
        int row = ui->tableWidget->row(items.at(0));
        list.del(row);
        list.save();
        updateTableWidget(ui->tableWidget, list);
    }else{
        QMessageBox::information(this, "操作提示", "删除失败，未选中要删除的信息项");
    }
}

void RecordInfoListDialog::on_pushButtonSearch_clicked()
{
    SearchDialog dlg(this);
    QStringList s;
    s << "日期" << "营业员工号" << "业务类型" << "金额";
    dlg.setSelect(s);
    if(dlg.exec() == QDialog::Accepted){
        while(ui->tableWidget->rowCount()){
            ui->tableWidget->removeRow(0);
        }
        for(auto& item : list.data) {
            if(dlg.select == "日期" && dlg.word == item.date.toString("yyyy/MM/dd")){
                addTableWidget(ui->tableWidget, item);
            }
            if(dlg.select == "营业员工号" && dlg.word == item.job_number){
                addTableWidget(ui->tableWidget, item);
            }
            if(dlg.select == "业务类型" && dlg.word == item.type){
                addTableWidget(ui->tableWidget, item);
            }
            if(dlg.select == "金额" && dlg.word == QString::number(item.amount)){
                addTableWidget(ui->tableWidget, item);
            }
        }
    }
}

void RecordInfoListDialog::on_pushButtonRefresh_clicked()
{
    updateTableWidget(ui->tableWidget, list);
}
