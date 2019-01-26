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
    if (!p_QSqlQuery->exec(QuerySearch)) {
        qDebug() << "Unable to execute query - exiting";
    }else{
        QSqlRecord rec = p_QSqlQuery->record();
        p_QSqlQuery->next();
        int id_genre = 0;
        id_genre = p_QSqlQuery->value(rec.indexOf(indexOf)).toInt();
        if(id_genre==0)
        {
            QMessageBox::warning(this,
                                 "Внимание",
                                 "Добавили");

            //if (!p_QSqlQuery->exec(QueryAdd)) {
            //    qDebug() << "Unable to do insert operation";
            //}
        }else {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Найденно совпадение", "Данный жанр уже есть базе данных внести его ?",
                                          QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {

                qDebug() << "Yes was clicked";
                QApplication::quit();
            } else {
                qDebug() << "Yes was *not* clicked";
            }
        }
    }
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
        add_new_item(QueryFactory::search_by_name_publisher_cache(name_publisher),
                     QueryFactory::add_row_in_table_publisher(name_publisher),
                     "id_publisher");
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
        add_new_item(QueryFactory::search_by_bbk_cache(name_publisher),
                     QueryFactory::add_row_in_table_bbk(name_publisher),
                     "id_bbk");
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
        add_new_item(QueryFactory::search_by_udc_cache(name_publisher),
                     QueryFactory::add_row_in_table_udc(name_publisher),
                     "id_udc");
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
        QSqlQuery *p_QSqlQuery = p_connect->getQueryData();
        if (!p_QSqlQuery->exec(QueryFactory::search_by_ISBN_cache(ISBN))) {
            qDebug() << "Unable to execute query - exiting";
        }else{
            QSqlRecord rec = p_QSqlQuery->record();
            p_QSqlQuery->next();
            int found = 0;
            found = p_QSqlQuery->value(rec.indexOf("id_books")).toInt();
            if(found==0)
            {


            }else {
                QMessageBox::warning(this,
                                     "Внимание",
                                     "Попытка добавить одинаковый ISBN");
            }
        }
        delete p_QSqlQuery;
    }
}

void DialogAddBook::on_pushButton_addlistiem_author_clicked()
{
    author_add = new DialogTextResponse(this,
                                        this->p_connect,
                                        "SELECT author_record FROM librarydb.author;");
    author_add->exec();
    listAuthor.append(author_add->getResultDialog());
    listModelAuthor->setStringList(listAuthor);
    ui->listView_author->setModel(listModelAuthor);
}

void DialogAddBook::on_pushButton_addlistiem_genre_clicked()
{
    genre_add = new DialogTextResponse(this,
                                       this->p_connect,
                                       "SELECT genre_record FROM librarydb.genre;");
    genre_add->exec();
    listGenre.append(genre_add->getResultDialog());
    listModelGenre->setStringList(listGenre);
    ui->listView_genre->setModel(listModelGenre);
}
