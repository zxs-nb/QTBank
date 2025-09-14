#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = nullptr);
    ~SearchDialog();

public:
    void setSelect(const QStringList& list);

private slots:
    void on_pushButton_clicked();

public:
    QString select;
    QString word;

private:
    Ui::SearchDialog *ui;
};

#endif
