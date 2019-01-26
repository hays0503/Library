#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include "dialogsearch.h"
#include "queryfactory.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotSelectionChange(const QItemSelection &, const QItemSelection &)
{
            QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();//Here you are getting the indexes of the selected rows

            //Now you can create your code using this information
            qDebug()<<selection.takeAt(0).data().toString();
            qDebug()<<"Signal !";
}

void MainWindow::slotChangeTable(QString query)
{
    db->setTableQuery(ui->tableView,query);
}

void MainWindow::OnDoubleClicked(const QModelIndex &index)
{
   QString a =(index.model()->data(index.model()->index(index.row(),index.column())).toString());
   int row = index.row();
   p_editForm = new editForm(nullptr,ui->tableView,row);
   p_editForm->show();
}

void MainWindow::on_Search_in_database_triggered()
{
    p_SearchDialogForm = new DialogSearch(nullptr,db);
    p_SearchDialogForm->show();
    connect(p_SearchDialogForm,
            SIGNAL(signal_changeTable(QString)),
            this,
            SLOT(slotChangeTable(QString))
            );
}

void MainWindow::on_Connect_to_database_triggered()
{
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    db = new DataBase();
    db->CreatConection("librarydb");
    ui->pushButton->setText("Go");
    connect(ui->tableView,
            SIGNAL(doubleClicked(QModelIndex)),
            this,
            SLOT(OnDoubleClicked(QModelIndex))
            );

}

void MainWindow::on_action_triggered()
{
    p_AddDialogForm = new DialogAddBook(nullptr,db);
    p_AddDialogForm->show();
}
