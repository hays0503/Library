#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>
#include <editform.h>

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
private slots:
    void on_action_triggered();
    void OnDoubleClicked(const QModelIndex &index);


public slots:
    void slotSelectionChange(const QItemSelection &, const QItemSelection &);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
