#ifndef PASSENGERLISTDIALOG_H
#define PASSENGERLISTDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include "data.h"

namespace Ui {
class RecordInfoListDialog;
}

class RecordInfoListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecordInfoListDialog(QWidget *parent = nullptr);
    ~RecordInfoListDialog();

public:
    void setAccount(AccountInfo* info);

private slots:
    //添加
    void on_pushButtonAdd_clicked();
    //删除
    void on_pushButtonDel_clicked();
    //查询
    void on_pushButtonSearch_clicked();
    //刷新
    void on_pushButtonRefresh_clicked();

private:
    void updateTableWidget(QTableWidget* widget, const RecordInfoList& list);

private:
    void setTableWidget(QTableWidget* widget);
    void addTableWidget(QTableWidget* widget, const RecordInfo& info);

public:
    bool  ismodify;

private:
    Ui::RecordInfoListDialog *ui;
    AccountInfo* info;
    RecordInfoList list;
};

#endif
