#ifndef DIALOGSEARCH_H
#define DIALOGSEARCH_H

#include <QDialog>
#include <QListWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include "database.h"

namespace Ui {
class DialogSearch;
}

class DialogSearch : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSearch(QWidget *parent = nullptr,
                          DataBase *p_connect = nullptr);
    ~DialogSearch();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void editTextChanged(const QString &text);

signals:
    void signal_changeTable(QString item);

private:
    Ui::DialogSearch *ui;
    QCompleter *completer_genre;
    QCompleter *completer_author;

    void InitSearchList(DataBase *p_connect);
};

#endif // DIALOGSEARCH_H
