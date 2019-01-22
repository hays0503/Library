#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>
#include <editform.h>
#include "dialogsearch.h"
#include "database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    editForm *p_editForm;
    DialogSearch *p_dialogForm;
    DataBase *db;
private slots:
    void OnDoubleClicked(const QModelIndex &index);

    void on_Search_in_database_triggered();

    void on_Connect_to_database_triggered();



public slots:
    void slotSelectionChange(const QItemSelection &, const QItemSelection &);

    void slotChangeTable(QString item);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
