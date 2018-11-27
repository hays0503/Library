#ifndef EDITFORM_H
#define EDITFORM_H

#include <QWidget>
#include <QTableView>

namespace Ui {
class editForm;
}

class editForm : public QWidget
{
    Q_OBJECT

public:
    explicit editForm(QWidget *parent = nullptr,
                      QTableView *dataTable  = nullptr,
                      int indexRow  = -1);
    ~editForm();

private:
    Ui::editForm *ui;
};

#endif // EDITFORM_H
