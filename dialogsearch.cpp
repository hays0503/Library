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
                  qint32 row, QSharedPointer<QSqlTableModel> &Table)
{
    ui->progressBar->setValue(20);
    p_connect->setComboBox(comboBox,table_name,row,Table);
    ui->progressBar->setValue(40);
    comboBox->setMaxVisibleItems(15);
    ui->progressBar->setValue(60);
    comboBox->setEditable(true);
    ui->progressBar->setValue(80);
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
    ui->progressBar->setValue(0);
    switch (index) {
    case 1: if(!completeWorkComboBox[0]){
            InitComboBox(p_connect,
                         ui->comboBox_genre,
                         "genre",
                         1,p_Table_genre);}
            else{
            ui->comboBox_genre->setModel(p_Table_genre.data());
            ui->comboBox_genre->setModelColumn(1);
            }break;
    case 2: if(!completeWorkComboBox[1]){
            InitComboBox(p_connect,
                         ui->comboBox_author,
                         "author",
                         1,p_Table_author);}
            else{
            ui->comboBox_author->setModel(p_Table_author.data());
            ui->comboBox_author->setModelColumn(1);
            }
        break;


    case 3: if(!completeWorkComboBox[2]){
            InitComboBox(p_connect,
                         ui->comboBox_publisher,
                         "publisher",
                         1,p_Table_publisher);}
        else{
        ui->comboBox_publisher->setModel(p_Table_publisher.data());
        ui->comboBox_publisher->setModelColumn(1);
        }break;
    case 4: if(!completeWorkComboBox[3]){
            InitComboBox(p_connect,
                         ui->comboBox_ISBN,
                         "books",
                         8,p_Table_ISBN);}
        else{
        ui->comboBox_ISBN->setModel(p_Table_ISBN.data());
        ui->comboBox_ISBN->setModelColumn(1);
        }break;
    case 5: if(!completeWorkComboBox[4]){
            InitComboBox(p_connect,
                         ui->comboBox_udc,
                         "udc",
                         1,p_Table_udc);}
        else{
        ui->comboBox_udc->setModel(p_Table_udc.data());
        ui->comboBox_udc->setModelColumn(1);
        }break;
    case 6: if(!completeWorkComboBox[5]){
            InitComboBox(p_connect,
                         ui->comboBox_bbk,
                         "bbk",
                         1,p_Table_bbk);}
        else{
        ui->comboBox_bbk->setModel(p_Table_bbk.data());
        ui->comboBox_bbk->setModelColumn(1);
        }break;
    }
    if(!completeWorkComboBox[index-1])
        completeWorkComboBox[index-1] = true;
    ui->progressBar->setValue(100);

}

