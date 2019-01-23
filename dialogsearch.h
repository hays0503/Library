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
    void editTextChanged(const QString &text);
    void on_checkBox_genre_stateChanged(int arg1);

    void on_checkBox_publisher_stateChanged(int arg1);

    void on_checkBox_udc_stateChanged(int arg1);

    void on_checkBox_author_stateChanged(int arg1);

    void on_checkBox_ISBN_stateChanged(int arg1);

    void on_checkBox_bbk_stateChanged(int arg1);

    void on_pushButton_name_book_clicked();

    void on_pushButton_genre_clicked();

    void on_pushButton_author_clicked();

    void on_pushButton_publisher_clicked();

    void on_pushButton_ISBN_clicked();

    void on_pushButton_udc_clicked();

    void on_pushButton_bbk_clicked();

    void on_pushButton_release_date_book_clicked();

    void on_tabWidget_currentChanged(int index);

signals:
    void signal_changeTable(QString query);

private:
    Ui::DialogSearch *ui;
    QCompleter *completer_genre;
    QCompleter *completer_author;
    QCompleter *completer_ISBN;
    QCompleter *completer_publisher;
    QCompleter *completer_udc;
    QCompleter *completer_bbk;
    QCompleter *completer_release_date_book;

    DataBase *p_connect;

    void InitSearchList(DataBase *p_connect);
};

#endif // DIALOGSEARCH_H
