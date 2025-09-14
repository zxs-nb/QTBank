#ifndef DATA_H
#define DATA_H

#include <QString>
#include <QTime>
#include <QVector>
#include <QFile>
#include <QTextStream>

//账户信息
class AccountInfo {
public:
    AccountInfo() : amount(0), loss(0), next(nullptr) {

    }

public:
    //从文件中加载数据
    bool load(QTextStream& input) {
        input >> id;
        input >> name;
        input >> password;
        input >> address;
        input >> category;
        input >> amount;
        input >> loss;
        QString create_str;
        input >> create_str;
        create_date = QDateTime::fromString(create_str, "yyyy/MM/dd#hh:mm:ss");
        QString loss_str;
        input >> loss_str;
        if(loss) {
            loss_date = QDateTime::fromString(loss_str, "yyyy/MM/dd#hh:mm:ss");
        }
        return !input.atEnd();
    }

    //将数据写入到文件
    void save(QTextStream& output) const {
        output << id << " ";
        output << name << " ";
        output << password << " ";
        output << address << " ";
        output << category << " ";
        output << amount << " ";
        output << loss << " ";
        output << create_date.toString("yyyy/MM/dd#hh:mm:ss") << " ";
        if(loss){
            output << loss_date.toString("yyyy/MM/dd#hh:mm:ss") << " ";
        }else {
            output << " - ";
        }
        output << "\n";
    }

    double interestRate() const {
        if(category == "定期1年") {
            return 1.98;
        }
        if(category == "定期3年") {
            return 2.25;
        }
        if(category == "定期5年") {
            return 3.5;
        }
        return 0;
    }

    double interest() const {
        return (interestRate() * 0.01) * amount;
    }

public:
    QString id;             //账号
    QString name;           //姓名
    QString password;       //密码
    QString address;        //地址
    QString category;       //储种
    double amount;          //余额
    int loss;               //是否挂失
    QDateTime create_date;  //开户日期
    QDateTime loss_date;    //挂失日期
    AccountInfo *next;      //下一个节点
};

//业务信息
class RecordInfo {
public:
    RecordInfo() : amount(0) {

    }

public:
    //从文件中加载数据
    bool load(QTextStream& input) {
        QString date_str;
        input >> date_str;
        input >> amount;
        input >> job_number;
        input >> type;
        date = QDateTime::fromString(date_str, "yyyy/MM/dd#hh:mm:ss");
        return !input.atEnd();
    }

    //将数据写入到文件
    void save(QTextStream& output) const {
        output << date.toString("yyyy/MM/dd#hh:mm:ss") << " ";
        output << amount << " ";
        output << job_number << " ";
        output << type << " ";
        output << "\n";
    }

public:
    QDateTime date;      //日期
    double amount;       //金额
    QString job_number;  //营业员工号
    QString type;        //业务类型
};

//账户信息表
class AccountInfoList {
public:
    AccountInfoList(): head(nullptr) {

    }

public:
    //设置文件名
    void setName(const QString& name);
    //添加账户信息
    bool add(const AccountInfo& info);
    //删除账户信息
    bool del(const QString& id);
    //根据账户账号查找账户信息
    AccountInfo* find(const QString &id);

public:
    //从文件中加载数据
    void load();
    //将数据写入到文件
    void save() const;

public:
    QString name;               //文件名
    AccountInfo* head;          //头结点指针
};

//业务信息列表
class RecordInfoList {
public:
    //设置文件名
    void setName(const QString& name);
    //添加业务信息
    void add(const RecordInfo& info);
    //删除业务信息
    void del(int index);
    //根据日期查找业务信息
    RecordInfo* find(const QString &date);

public:
    void load();
    void save() const;

public:
    QString name;               //文件名
    QVector<RecordInfo> data;   //业务信息列表
};

#endif
