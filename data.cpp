#include "res.rc"
#include "data.h"

void AccountInfoList::setName(const QString &name)
{
    this->name = name;
}

bool AccountInfoList::add(const AccountInfo &info)
{
    if(!find(info.id)){
        AccountInfo* node = new AccountInfo(info);

        if (head) {
            AccountInfo* cursor = head;
            while (cursor->next) {
                cursor = cursor->next;
            }
            cursor->next = node;
        } else {
            head = node;
        }

        return true;
    }
    return false;
}

bool AccountInfoList::del(const QString &id)
{
    if (head) {
        if (head->id == id) {
            AccountInfo* node = head;
            /*删除节点为首节点*/
            head = head->next;
            delete node;
            return true;
        } else {
            AccountInfo* cursor = head;
            while (cursor->next) {
                /*找到要删除节点的上一个节点*/
                if (cursor->next->id == id) {
                    /*将上一个节点指向删除节点的下一个节点*/
                    AccountInfo* node = cursor->next;
                    cursor->next = node->next;
                    /*删除该节点*/
                    delete node;
                    return true;
                }
                cursor = cursor->next;
            }
        }
    }
    return head;
}

AccountInfo *AccountInfoList::find(const QString &id)
{
    AccountInfo* cursor = head;
    while(cursor) {
        if(cursor->id == id) {
            return cursor;
        }
        cursor = cursor->next;
    }
    return nullptr;
}

void AccountInfoList::load()
{
    QFile file(name + ".txt");
    if(file.open(QFile::ReadOnly | QIODevice::Text)){
        AccountInfo info;
        QTextStream input(&file);
        while(true){
            if(!info.load(input)) break;
            add(info);
        }
    }
}

void AccountInfoList::save() const
{
    QFile file(name + ".txt");
    if(file.open(QFile::WriteOnly | QIODevice::Text)){
        QTextStream output(&file);
        AccountInfo* cursor = head;
        while(cursor) {
            cursor->save(output);
            cursor = cursor->next;
        }
    }
}

void RecordInfoList::setName(const QString &name)
{
    this->name = name;
}

void RecordInfoList::add(const RecordInfo &info)
{
    data.append(info);
}

void RecordInfoList::del(int index)
{
    data.remove(index);
}

RecordInfo *RecordInfoList::find(const QString &date)
{
    for(auto& item : data){
        if(item.date.toString("yyyy/MM/dd") == date){
            return &item;
        }
    }
    return nullptr;
}

void RecordInfoList::load()
{
    QFile file(name + ".txt");
    if(file.open(QFile::ReadOnly | QIODevice::Text)){
        RecordInfo info;
        QTextStream input(&file);
        while(true){
            if(!info.load(input)) break;
            data.append(info);
        }
    }
}

void RecordInfoList::save() const
{
    QFile file(name + ".txt");
    if(file.open(QFile::WriteOnly | QIODevice::Text)){
        QTextStream output(&file);
        for(auto& info : data){
            info.save(output);
        }
    }
}
