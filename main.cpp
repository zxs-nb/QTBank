#include "accountinfolistwindow.h"

#include <QApplication>
#include <QFile>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss("://res/qss/style9.qss");
    if(!qss.open(QFile::ReadOnly)){
        QMessageBox::critical(nullptr, "错误提示", "未能成功加载qss");
    }
    a.setStyleSheet(qss.readAll());
    AccountInfoListWindow w;
    w.show();
    return a.exec();
}
