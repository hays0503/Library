#ifndef DIALOGSEARCH_H
#define DIALOGSEARCH_H

#include <QDialog>
#include <QListWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include "database.h"
#include "dialogtextresponse.h"

namespace Ui {
class DialogSearch;
}

class DialogSearch : public QDialog
{
    Q_OBJECT

public:
    void InitComboBox(DataBase *p_connect,
                      QComboBox *comboBox,
                      QString table_name,
                      qint32 row, QSharedPointer<QSqlTableModel> &Table);

    void InitCompliter(DataBase *p_connect,
                       QComboBox *comboBox,
                       QCompleter *completer_name,
                       QString queru_completer,
                       int arg1);

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

    bool completeWorkComboBox[6] = {false};

    QSharedPointer<QSqlTableModel> p_Table_genre;
    QSharedPointer<QSqlTableModel> p_Table_author;
    QSharedPointer<QSqlTableModel> p_Table_ISBN;
    QSharedPointer<QSqlTableModel> p_Table_publisher;
    QSharedPointer<QSqlTableModel> p_Table_udc;
    QSharedPointer<QSqlTableModel> p_Table_bbk;
    QSharedPointer<QSqlTableModel> p_Table_release_date_book;

    qint32 *p_integer = new qint32;


    DataBase *p_connect;

    DialogTextResponse *dialog_add_genre;

    void InitSearchList(DataBase *p_connect);
};

#endif // DIALOGSEARCH_H
