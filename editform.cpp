#include "editform.h"
#include "ui_editform.h"

editForm::editForm(QWidget *parent,
                   QTableView *dataTable,
                   int indexRow) :
    QWidget(parent),
    ui(new Ui::editForm)
{
    ui->setupUi(this);
    ui->plainTextEdit->setPlainText(
            dataTable->model()->data(
            dataTable->model()->index(indexRow,0)).toString());
    ui->plainTextEdit_2->setPlainText(
            dataTable->model()->data(
            dataTable->model()->index(indexRow,1)).toString());
    ui->plainTextEdit_3->setPlainText(
            dataTable->model()->data(
            dataTable->model()->index(indexRow,2)).toString());
    ui->plainTextEdit_4->setPlainText(
            dataTable->model()->data(
            dataTable->model()->index(indexRow,3)).toString());
    ui->plainTextEdit_5->setPlainText(
            dataTable->model()->data(
            dataTable->model()->index(indexRow,4)).toString());
    ui->plainTextEdit_6->setPlainText(
            dataTable->model()->data(
            dataTable->model()->index(indexRow,5)).toString());
    ui->plainTextEdit_7->setPlainText(
            dataTable->model()->data(
            dataTable->model()->index(indexRow,6)).toString());
}

editForm::~editForm()
{
    delete ui;
}
