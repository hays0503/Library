#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"


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

void MainWindow::on_action_triggered()
{
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    DataBase *db = new DataBase();
    db->CreatConection("librarydb");
    db->setTableQuery(ui->tableView);
    ui->pushButton->setText("Go");
    /*connect(ui->tableView->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            SLOT(slotSelectionChange(const QItemSelection &, const QItemSelection &))
           );*/
    connect(ui->tableView,
            SIGNAL(doubleClicked(QModelIndex)),
            this,
            SLOT(OnDoubleClicked(QModelIndex))
            );
}

void MainWindow::slotSelectionChange(const QItemSelection &, const QItemSelection &)
{
            QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();//Here you are getting the indexes of the selected rows

            //Now you can create your code using this information
            qDebug()<<selection.takeAt(0).data().toString();
            qDebug()<<"Signal !";
}

void MainWindow::OnDoubleClicked(const QModelIndex &index)
{
   QString a =(index.model()->data(index.model()->index(index.row(),index.column())).toString());
   int row = index.row();
   p_editForm = new editForm(nullptr,ui->tableView,row);
   p_editForm->show();
}
