#ifndef DIALOGTEXTRESPONSE_H
#define DIALOGTEXTRESPONSE_H

#include <QDialog>
#include "database.h"

namespace Ui {
class DialogTextResponse;
}

class DialogTextResponse : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTextResponse(QWidget *parent = nullptr,
                                DataBase *p_connect = nullptr,
                                QString const query = "NULL");
    ~DialogTextResponse();

    void InitCompliter(DataBase *p_connect,
                       QLineEdit *LineEdit,
                       QCompleter *completer_name,
                       QString queru_completer,
                       int arg1);


    QString getResultDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogTextResponse *ui;
    QCompleter *completer_item;
    QString result;
};

#endif // DIALOGTEXTRESPONSE_H
