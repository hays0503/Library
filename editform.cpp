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
            dataTable->model()->index(indexRow,2)).toString());
    ui->plainTextEdit_1->setPlainText(
            dataTable->model()->data(
            dataTable->model()->index(indexRow,3)).toString());
    ui->plainTextEdit_2->setPlainText(
            dataTable->model()->data(
            dataTable->model()->index(indexRow,4)).toString());
    ui->plainTextEdit_3->setPlainText(
            dataTable->model()->data(
            dataTable->model()->index(indexRow,5)).toString());
    ui->plainTextEdit_4->setPlainText(
            dataTable->model()->data(
            dataTable->model()->index(indexRow,6)).toString());
    ui->plainTextEdit_5->setPlainText(
            dataTable->model()->data(
            dataTable->model()->index(indexRow,7)).toString());
    ui->plainTextEdit_6->setPlainText(
            dataTable->model()->data(
            dataTable->model()->index(indexRow,8)).toString());
    ui->plainTextEdit_7->setPlainText(
            dataTable->model()->data(
            dataTable->model()->index(indexRow,9)).toString());
    ui->plainTextEdit_8->setPlainText(
            dataTable->model()->data(
            dataTable->model()->index(indexRow,10)).toString());
    ui->plainTextEdit_9->setPlainText(
            dataTable->model()->data(
            dataTable->model()->index(indexRow,11)).toString());
}

editForm::~editForm()
{
    delete ui;
}
