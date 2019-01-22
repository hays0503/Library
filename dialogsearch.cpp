#include "dialogsearch.h"
#include "ui_dialogsearch.h"
#include <QCompleter>




DialogSearch::DialogSearch(QWidget *parent,
                           DataBase *p_connect) :
    QDialog(parent),
    ui(new Ui::DialogSearch)
{
    ui->setupUi(this);

    InitSearchList(p_connect);

}

DialogSearch::~DialogSearch()
{
    delete ui;
}

void InitComboBox(DataBase *p_connect,
                  QComboBox *comboBox,
                  QString table_name,
                  qint32 row,
                  QCompleter *completer_name,
                  QString queru_completer)
{
    p_connect->setComboBox(comboBox,table_name,row);
    completer_name = new QCompleter();
    p_connect->setCompleter(completer_name,queru_completer);
    completer_name->setModelSorting(QCompleter::UnsortedModel);
    completer_name->setCaseSensitivity(Qt::CaseInsensitive);
    completer_name->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    comboBox->setMaxVisibleItems(4);
    comboBox->setEditable(true);
    comboBox->setCompleter(completer_name);
}

void DialogSearch::InitSearchList(DataBase *p_connect)
{
    connect(ui->comboBox_genre,
            SIGNAL(editTextChanged(QString)),
            this,
            SLOT(editTextChanged(QString)));

    InitComboBox(p_connect,
                 ui->comboBox_genre,
                 "genre",
                 1,
                 completer_genre,
                 "SELECT genre_record FROM librarydb.genre;");

    InitComboBox(p_connect,
                 ui->comboBox_author,
                 "author",
                 1,
                 completer_author,
                 "SELECT author_record FROM librarydb.author;");

    InitComboBox(p_connect,
                 ui->comboBox_ISBN,
                 "books",
                 8,
                 completer_ISBN,
                 "SELECT isbn FROM librarydb.books;");

    InitComboBox(p_connect,
                 ui->comboBox_publisher,
                 "publisher",
                 1,
                 completer_publisher,
                 "SELECT publisher_record FROM librarydb.publisher;");

    InitComboBox(p_connect,
                 ui->comboBox_udc,
                 "udc",
                 1,
                 completer_udc,
                 "SELECT udc_record FROM librarydb.udc;");

    InitComboBox(p_connect,
                 ui->comboBox_bbk,
                 "bbk",
                 1,
                 completer_bbk,
                 "SELECT bbk_record FROM librarydb.bbk;");

}
void DialogSearch::on_buttonBox_clicked(QAbstractButton *button)
{
    QString item =    //ui->comboBox_genre->itemText(ui->comboBox_genre->currentIndex());
                      //ui->comboBox_author->itemText(ui->comboBox_author->currentIndex());
                        QVariant(ui->spinBox_release_date_book->value()).toString();
    emit signal_changeTable(item);
    this->close();
}

void DialogSearch::editTextChanged(const QString &text)
{
    qDebug()<<text;

}


