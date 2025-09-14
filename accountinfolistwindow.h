#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "data.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AccountInfoListWindow; }
QT_END_NAMESPACE

class AccountInfoListWindow : public QMainWindow
{
    Q_OBJECT

public:
    AccountInfoListWindow(QWidget *parent = nullptr);
    ~AccountInfoListWindow();

private slots:
    //储户登录
    void on_pushButtonLogin_clicked();
    //添加账户信息
    void on_pushButtonAdd_clicked();
    //删除账户信息
    void on_pushButtonDel_clicked();
    //查看账户信息
    void on_pushButtonDetails_clicked();
    //搜索账户信息
    void on_pushButtonSearch_clicked();
    //刷新账户信息
    void on_pushButtonRefresh_clicked();
    //查看存取款记录信息
    void on_pushButtonOpen_clicked();

private:
    //添加账户信息
    void addAccountInfo(QTableWidget* widget, AccountInfoList& list);
    //删除账户信息
    void delAccountInfo(QTableWidget* widget, AccountInfoList& list);
    //修改账户信息
    void detailsAccountInfo(QTableWidget* widget, AccountInfoList& list);
    //查看业务信息
    void openAccountInfo(QTableWidget* widget, AccountInfoList& list);

    void updateMessage();
    double countReserve();

private:
    static void updateTableWidget(QTableWidget* widget, const AccountInfoList& list);

private:
    static void setTableWidget(QTableWidget* widget);
    static void addTableWidget(QTableWidget* widget, const AccountInfo& info);

private:
    Ui::AccountInfoListWindow *ui;
    AccountInfoList list; //账户信息表
};

#endif
