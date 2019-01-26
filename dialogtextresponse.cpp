#include "dialogtextresponse.h"
#include "ui_dialogtextresponse.h"
#include "queryfactory.h"

DialogTextResponse::DialogTextResponse(QWidget *parent,
                                       DataBase *p_connect,
                                       const QString query):
    QDialog(parent),
    ui(new Ui::DialogTextResponse)
{
    ui->setupUi(this);
    qDebug()<<query;
    InitCompliter(p_connect,
                  ui->lineEdit,
                  completer_item,
                  query,
                  2);

}

DialogTextResponse::~DialogTextResponse()
{
    delete ui;
}

void DialogTextResponse::InitCompliter(DataBase *p_connect, QLineEdit *LineEdit, QCompleter *completer_name, QString queru_completer, int arg1)
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
    LineEdit->setCompleter(completer_name);

}

QString DialogTextResponse::getResultDialog()
{
    return result;
}

void DialogTextResponse::on_buttonBox_accepted()
{
    this->accept();
    result = ui->lineEdit->text();
}
