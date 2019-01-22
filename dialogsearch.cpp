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

void DialogSearch::InitSearchList(DataBase *p_connect)
{
    p_connect->setComboBox(ui->comboBox_genre,"genre",1);
    completer_genre = new QCompleter(this);
    p_connect->setCompleter(completer_genre,"SELECT genre_record FROM librarydb.genre;");
    completer_genre->setCaseSensitivity(Qt::CaseInsensitive);
    completer_genre->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    ui->comboBox_genre->setEditable(true);
    ui->comboBox_genre->setCompleter(completer_genre);
    connect(ui->comboBox_genre,
            SIGNAL(editTextChanged(QString)),
            this,
            SLOT(editTextChanged(QString)));


    p_connect->setComboBox(ui->comboBox_author,"author",1);
    completer_author = new QCompleter(this);
    p_connect->setCompleter(completer_author,"SELECT author_record FROM librarydb.author;");
    completer_author->setCaseSensitivity(Qt::CaseInsensitive);
    completer_author->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    ui->comboBox_author->setEditable(true);
    ui->comboBox_author->setCompleter(completer_author);

}
void DialogSearch::on_buttonBox_clicked(QAbstractButton *button)
{
    QString item =    //ui->comboBox_genre->itemText(ui->comboBox_genre->currentIndex());
                        ui->comboBox_author->itemText(ui->comboBox_author->currentIndex());
    emit signal_changeTable(item);
    this->close();
}

void DialogSearch::editTextChanged(const QString &text)
{
    qDebug()<<text;

}


