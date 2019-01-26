#include "dialogsearch.h"
#include "ui_dialogsearch.h"
#include <QCompleter>
#include "queryfactory.h"




DialogSearch::DialogSearch(QWidget *parent,
                           DataBase *p_connect) :
    QDialog(parent),
    ui(new Ui::DialogSearch)
{
    ui->setupUi(this);
    this->move(35,35);
    this->setFocus();

    this->p_connect = p_connect;

    InitSearchList(p_connect);


}

DialogSearch::~DialogSearch()
{
    delete ui;
}

void DialogSearch::InitComboBox(DataBase *p_connect,
                  QComboBox *comboBox,
                  QString table_name,
                  qint32 row)
{
    ui->progressBar->setValue(20);
    ui->progressBar->setValue(25);
    ui->progressBar->setValue(30);
    p_connect->setComboBox(comboBox,table_name,row);
    ui->progressBar->setValue(40);
    ui->progressBar->setValue(35);
    ui->progressBar->setValue(50);
    comboBox->setMaxVisibleItems(4);
    ui->progressBar->setValue(60);
    ui->progressBar->setValue(65);
    ui->progressBar->setValue(70);
    comboBox->setEditable(true);
    ui->progressBar->setValue(80);
    ui->progressBar->setValue(85);
    ui->progressBar->setValue(90);
}

void DialogSearch::InitCompliter(DataBase *p_connect,
                   QComboBox *comboBox,
                   QCompleter *completer_name,
                   QString queru_completer,
                   int arg1)
{
        completer_name = new QCompleter();
        p_connect->setCompleter(completer_name,queru_completer);
        completer_name->setModelSorting(QCompleter::UnsortedModel);
        completer_name->setCaseSensitivity(Qt::CaseInsensitive);
        if(arg1==2)
        {
            completer_name->setCompletionMode(QCompleter::UnfilteredPopupCompletion);

        }else {
            completer_name->setCompletionMode(QCompleter::InlineCompletion);
        }
        comboBox->setCompleter(completer_name);
}


void DialogSearch::InitSearchList(DataBase *p_connect)
{
    connect(ui->comboBox_genre,
            SIGNAL(editTextChanged(QString)),
            this,
            SLOT(editTextChanged(QString)));
}

void DialogSearch::editTextChanged(const QString &text)
{
    qDebug()<<text;

}

void DialogSearch::on_checkBox_genre_stateChanged(int arg1)
{
        InitCompliter(p_connect,
                      ui->comboBox_genre,
                      completer_genre,
                      "SELECT genre_record FROM librarydb.genre LIMIT 3000;",
                      arg1);
}

void DialogSearch::on_checkBox_publisher_stateChanged(int arg1)
{
    InitCompliter(p_connect,
                 ui->comboBox_publisher,
                 completer_publisher,
                 "SELECT publisher_record FROM librarydb.publisher LIMIT 3000;",
                  arg1);
}

void DialogSearch::on_checkBox_udc_stateChanged(int arg1)
{
    InitCompliter(p_connect,
                 ui->comboBox_udc,
                 completer_udc,
                 "SELECT udc_record FROM librarydb.udc LIMIT 3000;",
                 arg1);
}

void DialogSearch::on_checkBox_author_stateChanged(int arg1)
{
    InitCompliter(p_connect,
                 ui->comboBox_author,
                 completer_author,
                 "SELECT author_record FROM librarydb.author LIMIT 3000;",
                  arg1);
}

void DialogSearch::on_checkBox_ISBN_stateChanged(int arg1)
{
    InitCompliter(p_connect,
                 ui->comboBox_ISBN,
                 completer_ISBN,
                 "SELECT isbn FROM librarydb.books LIMIT 3000;",
                  arg1);
}

void DialogSearch::on_checkBox_bbk_stateChanged(int arg1)
{
    InitCompliter(p_connect,
                 ui->comboBox_bbk,
                 completer_bbk,
                 "SELECT bbk_record FROM librarydb.bbk LIMIT 3000;",
                  arg1);
}

void DialogSearch::on_pushButton_name_book_clicked()
{
    ui->progressBar->setValue(10);
    QString query = ui->line_name_book->text();
    ui->progressBar->setValue(20);
    query = QueryFactory::search_by_book_name_cache(query);
    ui->progressBar->setValue(40);
    emit signal_changeTable(query);
    ui->progressBar->setValue(90);
    ui->progressBar->setValue(100);
    this->close();
}

void DialogSearch::on_pushButton_genre_clicked()
{
    ui->progressBar->setValue(10);
    QString query = ui->comboBox_genre->itemText(ui->comboBox_genre->currentIndex());
    ui->progressBar->setValue(20);
    query = QueryFactory::search_by_genre_name_cache(query);
    ui->progressBar->setValue(50);
    emit signal_changeTable(query);
    ui->progressBar->setValue(100);
    this->close();
}

void DialogSearch::on_pushButton_author_clicked()
{
    ui->progressBar->setValue(10);
    QString query = ui->comboBox_author->itemText(ui->comboBox_author->currentIndex());
    ui->progressBar->setValue(50);
    query = QueryFactory::search_by_author_name_cache(query);
    ui->progressBar->setValue(80);
    emit signal_changeTable(query);
    ui->progressBar->setValue(100);
    this->close();
}

void DialogSearch::on_pushButton_publisher_clicked()
{
    ui->progressBar->setValue(10);
    QString query = ui->comboBox_publisher->itemText(ui->comboBox_publisher->currentIndex());
    ui->progressBar->setValue(50);
    query = QueryFactory::search_by_name_publisher_cache(query);
    ui->progressBar->setValue(80);
    emit signal_changeTable(query);
    ui->progressBar->setValue(100);
    this->close();
}

void DialogSearch::on_pushButton_ISBN_clicked()
{
    ui->progressBar->setValue(10);
    QString query = ui->comboBox_ISBN->itemText(ui->comboBox_ISBN->currentIndex());
    ui->progressBar->setValue(50);
    query = QueryFactory::search_by_ISBN_cache(query);
    ui->progressBar->setValue(80);
    emit signal_changeTable(query);
    ui->progressBar->setValue(100);
    this->close();
}

void DialogSearch::on_pushButton_udc_clicked()
{
    ui->progressBar->setValue(10);
    QString query = ui->comboBox_udc->itemText(ui->comboBox_udc->currentIndex());
    ui->progressBar->setValue(50);
    query = QueryFactory::search_by_udc_cache(query);
    ui->progressBar->setValue(80);
    emit signal_changeTable(query);
    ui->progressBar->setValue(100);
    this->close();
}

void DialogSearch::on_pushButton_bbk_clicked()
{
    ui->progressBar->setValue(10);
    QString query = ui->comboBox_bbk->itemText(ui->comboBox_bbk->currentIndex());
    ui->progressBar->setValue(50);
    query = QueryFactory::search_by_udc_cache(query);
    ui->progressBar->setValue(80);
    emit signal_changeTable(query);
    ui->progressBar->setValue(100);
    this->close();
}

void DialogSearch::on_pushButton_release_date_book_clicked()
{
    ui->progressBar->setValue(10);
    QString query = QVariant(ui->spinBox_release_date_book->value()).toString();
    ui->progressBar->setValue(50);
    query = QueryFactory::search_by_release_date_book(query);
    ui->progressBar->setValue(80);
    emit signal_changeTable(query);
    ui->progressBar->setValue(100);
    this->close();
}

void DialogSearch::on_tabWidget_currentChanged(int index)
{
    qDebug()<<index;
    ui->progressBar->setValue(0);
    switch (index) {
    case 1: InitComboBox(p_connect,
                         ui->comboBox_genre,
                         "genre",
                         1); break;
    case 2: InitComboBox(p_connect,
                         ui->comboBox_author,
                         "author",
                         1);break;
    case 3: InitComboBox(p_connect,
                         ui->comboBox_publisher,
                         "publisher",
                         1);break;
    case 4: InitComboBox(p_connect,
                         ui->comboBox_ISBN,
                         "books",
                         8);break;
    case 5: InitComboBox(p_connect,
                         ui->comboBox_udc,
                         "udc",
                         1);break;
    case 6: InitComboBox(p_connect,
                         ui->comboBox_bbk,
                         "bbk",
                         1);break;
    }
    ui->progressBar->setValue(100);

}

