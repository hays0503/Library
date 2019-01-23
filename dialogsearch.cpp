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

    this->p_connect = p_connect;

    InitSearchList(p_connect);


}

DialogSearch::~DialogSearch()
{
    delete ui;
}

void InitComboBox(DataBase *p_connect,
                  QComboBox *comboBox,
                  QString table_name,
                  qint32 row)
{
    p_connect->setComboBox(comboBox,table_name,row);
//    completer_name = new QCompleter();
//    p_connect->setCompleter(completer_name,queru_completer);
//    completer_name->setModelSorting(QCompleter::UnsortedModel);
//    completer_name->setCaseSensitivity(Qt::CaseInsensitive);
//    completer_name->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    comboBox->setMaxVisibleItems(4);
    comboBox->setEditable(true);
    //comboBox->setCompleter(completer_name);
}

void InitCompliter(DataBase *p_connect,
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
    QString query = ui->line_name_book->text();
    query = QueryFactory::search_by_book_name_cache(query);
    emit signal_changeTable(query);
    this->close();
}

void DialogSearch::on_pushButton_genre_clicked()
{
    QString query = ui->comboBox_genre->itemText(ui->comboBox_genre->currentIndex());
    query = QueryFactory::search_by_genre_name_cache(query);
    emit signal_changeTable(query);
    this->close();
}

void DialogSearch::on_pushButton_author_clicked()
{
    QString query = ui->comboBox_author->itemText(ui->comboBox_author->currentIndex());
    query = QueryFactory::search_by_author_name_cache(query);
    emit signal_changeTable(query);
    this->close();
}

void DialogSearch::on_pushButton_publisher_clicked()
{
    QString query = ui->comboBox_publisher->itemText(ui->comboBox_publisher->currentIndex());
    query = QueryFactory::search_by_name_publisher(query);
    emit signal_changeTable(query);
    this->close();
}

void DialogSearch::on_pushButton_ISBN_clicked()
{
    QString query = ui->comboBox_ISBN->itemText(ui->comboBox_ISBN->currentIndex());
    query = QueryFactory::search_by_ISBN(query);
    emit signal_changeTable(query);
    this->close();
}

void DialogSearch::on_pushButton_udc_clicked()
{
    QString query = ui->comboBox_udc->itemText(ui->comboBox_udc->currentIndex());
    query = QueryFactory::search_by_udc(query);
    emit signal_changeTable(query);
    this->close();
}

void DialogSearch::on_pushButton_bbk_clicked()
{
    QString query = ui->comboBox_bbk->itemText(ui->comboBox_bbk->currentIndex());
    query = QueryFactory::search_by_udc(query);
    emit signal_changeTable(query);
    this->close();
}

void DialogSearch::on_pushButton_release_date_book_clicked()
{
    QString query = QVariant(ui->spinBox_release_date_book->value()).toString();
    query = QueryFactory::search_by_release_date_book(query);
    emit signal_changeTable(query);
    this->close();
}

void DialogSearch::on_tabWidget_currentChanged(int index)
{
    qDebug()<<index;
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

}
