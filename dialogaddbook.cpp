#include "dialogaddbook.h"
#include "ui_dialogaddbook.h"
#include "queryfactory.h"
#include <QMessageBox>


DialogAddBook::DialogAddBook(QWidget *parent,
                             DataBase *p_connect) :
    QDialog(parent),
    ui(new Ui::DialogAddBook)
{
    ui->setupUi(this);
    this->move(35,35);
    this->setFocus();
    this->p_connect = p_connect;

    p_connect->setComboBox(ui->comboBox_book_binding,
                           "book_binding_type",
                           1);

    listModelGenre = new QStringListModel(this);
    listModelAuthor = new QStringListModel(this);

}

DialogAddBook::~DialogAddBook()
{
    delete ui;
}

void DialogAddBook::add_new_item(QString QuerySearch,
                                 QString QueryAdd,
                                 QString indexOf)
{
    QSqlQuery *p_QSqlQuery = p_connect->getQueryData();
    int result = p_connect->SearchSQL(QuerySearch,indexOf);
    if(result!=0)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Найденно совпадение", "Данный жанр уже есть базе данных внести его ?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {

            qDebug() << "Yes was clicked";

        } else {
            qDebug() << "Yes was *not* clicked";
        }
    }else {
        QMessageBox::warning(this,
                             "Внимание",
                             "Добавили");

        if (!p_QSqlQuery->exec(QueryAdd)) {
            qDebug() << "Unable to do insert operation";
        }
    }
    result = p_connect->SearchSQL(QuerySearch,indexOf);
    qDebug()<<"RESULT "<<result;
    if(indexOf=="id_genre"){editableBook.id_genre.append(result);};
    if(indexOf=="id_author"){editableBook.id_author.append(result);};
    if(indexOf=="id_publisher"){editableBook.index_publisher=result;};
    if(indexOf=="id_bbk"){editableBook.index_bbk=result;};
    if(indexOf=="id_udc"){editableBook.index_udc=result;};
    delete p_QSqlQuery;
}

void DialogAddBook::on_pushButton_add_new_genre_clicked()
{
    bool bOk;
    QString name_genre = QInputDialog::getText( this,
                                                "Запрос",
                                                "Введите название жанра:",
                                                QLineEdit::Normal,
                                                "",
                                                &bOk
                                                );
    if (bOk) {
        add_new_item(QueryFactory::search_by_name_genre(name_genre),
                     QueryFactory::add_row_in_table_genre(name_genre),
                     "id_genre");
    }
}

void DialogAddBook::on_pushButton_add_author_clicked()
{
    bool bOk;
    QString name_author = QInputDialog::getText( this,
                                                "Запрос",
                                                "Введите имя автора:",
                                                QLineEdit::Normal,
                                                "",
                                                &bOk
                                                );
    if (bOk) {
        add_new_item(QueryFactory::search_by_name_author(name_author),
                     QueryFactory::add_row_in_table_author(name_author),
                     "id_author");

    }
}

void DialogAddBook::on_pushButton_add_new_publisher_clicked()
{
    bool bOk;
    QString name_publisher = QInputDialog::getText( this,
                                                "Запрос",
                                                "Введите имя автора:",
                                                QLineEdit::Normal,
                                                "",
                                                &bOk
                                                );
    if (bOk) {
        add_new_item(QueryFactory::search_name_publisher(name_publisher),
                     QueryFactory::add_row_in_table_publisher(name_publisher),
                     "id_publisher");
        ui->label_publisher->setText("Издатель установлен");
        ui->label_publisher->setStyleSheet("QLabel { color : rgb(0,255 , 0) }");

    }
}

void DialogAddBook::on_pushButton_add_bbk_clicked()
{
    bool bOk;
    QString name_publisher = QInputDialog::getText( this,
                                                "Запрос",
                                                "Введите ББК:",
                                                QLineEdit::Normal,
                                                "",
                                                &bOk
                                                );
    if (bOk) {
        add_new_item(QueryFactory::search_bbk(name_publisher),
                     QueryFactory::add_row_in_table_bbk(name_publisher),
                     "id_bbk");
        ui->label_bbk->setText("ББК установлен");
        ui->label_bbk->setStyleSheet("QLabel { color : rgb(0,255 , 0) }");
    }
}

void DialogAddBook::on_pushButton_add_udc_clicked()
{
    bool bOk;
    QString name_publisher = QInputDialog::getText( this,
                                                "Запрос",
                                                "Введите УДК:",
                                                QLineEdit::Normal,
                                                "",
                                                &bOk
                                                );
    if (bOk) {
        add_new_item(QueryFactory::search_udc(name_publisher),
                     QueryFactory::add_row_in_table_udc(name_publisher),
                     "id_udc");
        ui->label_udc->setText("УДК установлен");
        ui->label_udc->setStyleSheet("QLabel { color : rgb(0,255 , 0) }");
    }
}

void DialogAddBook::on_pushButton_add_ISBN_clicked()
{
    bool bOk;
    QString ISBN = QInputDialog::getText( this,
                                                "Запрос",
                                                "Введите ISBN:",
                                                QLineEdit::Normal,
                                                "",
                                                &bOk
                                                );
    if (bOk) {
        int result = p_connect->SearchSQL(QueryFactory::search_ISBN_book(ISBN),"id_books");
            if(result!=0)
            {
                QMessageBox::warning(this,
                                     "Внимание",
                                     "Попытка добавить одинаковый ISBN");
            }else {
                editableBook.isbn = ISBN;
                ui->label_ISBN->setText("ISBN установлен");
                ui->label_ISBN->setStyleSheet("QLabel { color : rgb(0,255 , 0) }");
            }
        }

}

void DialogAddBook::on_pushButton_addlistiem_author_clicked()
{
    author_add = new DialogTextResponse(this,
                                        this->p_connect,
                                        "SELECT author_record FROM librarydb.author;");
    author_add->exec();
    QString result = author_add->getResultDialog();
    if(result != "None result")
    {
        listAuthor.append(author_add->getResultDialog());
        listModelAuthor->setStringList(listAuthor);
        ui->listView_author->setModel(listModelAuthor);
        ui->label_author->setText("Автор(ы) установлен");
        ui->label_author->setStyleSheet("QLabel { color : rgb(0, 255, 0) }");
        int id_author = p_connect->SearchSQL(
        QueryFactory::search_by_name_author(result),
                    "id_author");
        editableBook.id_author.append(id_author);
    }
}

void DialogAddBook::on_pushButton_addlistiem_genre_clicked()
{
    genre_add = new DialogTextResponse(this,
                                       this->p_connect,
                                       "SELECT genre_record FROM librarydb.genre;");
    genre_add->exec();
    QString result = genre_add->getResultDialog();
    if(result != "None result")
    {
        listGenre.append(result);
        listModelGenre->setStringList(listGenre);
        ui->listView_genre->setModel(listModelGenre);
        ui->label_genre->setText("Жанр(ы) установлен");
        ui->label_genre->setStyleSheet("QLabel { color : rgb(0, 255, 0) }");
        int id_genre = p_connect->SearchSQL(
        QueryFactory::search_by_name_genre(result),
                    "id_genre");
        editableBook.id_genre.append(id_genre);
    }

}

void DialogAddBook::on_pushButton_rmlistiem_genre_clicked()
{
    listGenre.removeAt(ui->listView_genre->currentIndex().row());
    listModelGenre->setStringList(listGenre);
    ui->listView_genre->setModel(listModelGenre);
    if(listGenre.empty())
    {
        ui->label_genre->setText("Жанр не установлен");
        ui->label_genre->setStyleSheet("QLabel { color : rgb(255,0 , 0) }");
    }
}

void DialogAddBook::on_pushButton_rmlistiem_author_clicked()
{
    listAuthor.removeAt(ui->listView_author->currentIndex().row());
    listModelAuthor->setStringList(listAuthor);
    ui->listView_author->setModel(listModelAuthor);
    if(listAuthor.empty())
    {
        ui->label_author->setText("Жанр не установлен");
        ui->label_author->setStyleSheet("QLabel { color : rgb(255,0 , 0) }");
    }
}

void DialogAddBook::on_pushButton_addBook_clicked()
{
    editableBook.name_book = ui->line_name_book_2->text();
    editableBook.release_date_book = ui->spinBox_release_year->value();
    editableBook.number_of_pages_book = ui->spinBox_num_pages->value();
    editableBook.index_book_binding_type = ui->comboBox_book_binding->currentIndex();
    qDebug()<<"name_book "<<editableBook.name_book;
    qDebug()<<"editableBook.id_books "<<editableBook.id_books;
    qDebug()<<"editableBook.id_author[0] "<<editableBook.id_author[0];
    qDebug()<<"editableBook.id_genre[0] "<<editableBook.id_genre[0];
    qDebug()<<"editableBook.number_of_pages_book "<<editableBook.number_of_pages_book;
    qDebug()<<"editableBook.index_book_binding_type "<<editableBook.index_book_binding_type;
    qDebug()<<"editableBook.release_date_book "<<editableBook.release_date_book;
    qDebug()<<"editableBook.index_udc "<<editableBook.index_udc;
    qDebug()<<"editableBook.index_bbk "<<editableBook.index_bbk;
    qDebug()<<"editableBook.index_publisher "<<editableBook.index_publisher;
    qDebug()<<"editableBook.isbn "<<editableBook.isbn;
    qDebug()<<"editableBook.description_record "<<editableBook.description_record;
}
