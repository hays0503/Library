#ifndef DIALOGADDBOOK_H
#define DIALOGADDBOOK_H

#include <QDialog>
#include "database.h"
#include "dialogtextresponse.h"

namespace Ui {
class DialogAddBook;
}

struct book
{
    int id_books;
    QList<int> id_author;
    QList<int> id_genre;
    QString name_book;
    int number_of_pages_book;
    int index_book_binding_type;
    int release_date_book;
    int index_udc;
    int index_bbk;
    int index_publisher;
    QString isbn;
    QString description_record;
};

class DialogAddBook : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddBook(QWidget *parent = nullptr,
                           DataBase *p_connect = nullptr);
    ~DialogAddBook();


private slots:
    void on_pushButton_add_new_genre_clicked();

    void on_pushButton_add_author_clicked();

    void on_pushButton_add_new_publisher_clicked();

    void on_pushButton_add_bbk_clicked();

    void on_pushButton_add_udc_clicked();

    void on_pushButton_add_ISBN_clicked();

    void on_pushButton_addlistiem_author_clicked();

    void on_pushButton_addlistiem_genre_clicked();

    void on_pushButton_rmlistiem_genre_clicked();

    void on_pushButton_rmlistiem_author_clicked();

    void on_pushButton_addBook_clicked();

private:
    void add_new_item(QString QuerySearch,
                      QString QueryAdd,
                      QString indexOf);


    Ui::DialogAddBook *ui;
    DataBase *p_connect;
    DialogTextResponse *genre_add;
    QStringList listGenre;
    QStringListModel *listModelGenre;

    DialogTextResponse *author_add;
    QStringList listAuthor;
    QStringListModel *listModelAuthor;

    QList<book> Books;
    book editableBook;
};

#endif // DIALOGADDBOOK_H
