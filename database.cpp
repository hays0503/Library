#include "database.h"
#include "mainwindow.h"
#include "queryfactory.h"
#include <iostream>
#include <QTextStream>


DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

bool DataBase::CreatConection(QString NameDataBase = "")
{
    objMDB = QSqlDatabase::addDatabase("QMYSQL");// Microsoft Access
    objMDB.setDatabaseName(NameDataBase);
       objMDB.setHostName("127.0.0.1");
       objMDB.setPort(3306);
       objMDB.setUserName("hays0503");
       objMDB.setPassword("hays0503");

    if (objMDB.open()) {
           qDebug("Success!");
           return true;
    } else {
        qDebug()<<objMDB.lastError().text();
        //qDebug()<<connectString;
        return false;
    }

}

QSqlDatabase *DataBase::getObjMDB()
{
    return &objMDB;
}

void DataBase::setObjMDB(QSqlDatabase &value)
{
    objMDB = value;
}

bool DataBase::setTable(QTableView *tableView,QString TableName)
{
      qDebug()<<tableView;
      objTable = new QSqlTableModel(this);
      objTable ->setTable(TableName);
      if (!objTable ->select())
      {
          qDebug()<<objTable->lastError().databaseText();
          qDebug()<<objTable ->lastError().driverText();
          return false;
      }else tableView->setModel(objTable);
      return true;
}

QTextStream& qStdOut()
{
    static QTextStream ts( stdout );
    return ts;
}

bool DataBase::setTableQuery(QTableView *tableView, QString Query)
{
      objTableQuery = new QSqlQueryModel(this);
      objTableQuery->setQuery(Query);
      tableView->setModel(objTableQuery);
      tableView->update();
      tableView->show();
      return true;
}

void DataBase::setItemInBase(QVariant nameTable, QVariant item, QVariant cost, QVariant count, QDate date,QVariant Client)
{
  QSqlQuery Query;
  QString QueryStr = "INSERT INTO  "+nameTable.toString()+
                     " ([Номенклатура товара], [Кол-во],Цена,Дата,Клиент) VALUES('"
                      +item.toString()+"',"+count.toString()+","+cost.toString()+",#"
                      +date.toString("MM/dd/yyyy")+"#,'"+Client.toString()+"')";

  Query.prepare(QueryStr);
  if(!Query.exec())
    {
      qDebug()<<Query.lastError().databaseText();
      qDebug()<<Query.lastError().driverText();
      qDebug()<<Query.lastQuery();
    }
}

qint32 DataBase::getItemCount(QString TableName)
{
  objTable = new QSqlTableModel(this);
  objTable ->setTable(TableName);
  if (!objTable ->select())
  {
      qDebug()<<objTable->lastError().databaseText();
      qDebug()<<objTable ->lastError().driverText();
      return false;
  }else return objTable->rowCount();
}

QString DataBase::getItemProduct(QString TableName, qint32 Row)
{
  objTable ->setTable(TableName);
  if (!objTable ->select())
  {
      qDebug()<<objTable->lastError().databaseText();
      qDebug()<<objTable ->lastError().driverText();
      return "Error";
  }else return objTable->record(Row).value("Номенклатура товара").toString();
}

QSqlQueryModel *DataBase::getQueryData(QString Query)
{
    objTableQuery = new QSqlQueryModel(this);
    objTableQuery->setQuery(Query);
    return objTableQuery;
}

bool DataBase::setCompleter(QCompleter *completer, QString Query)
{
    qDebug()<<completer;
    objTableQuery = new QSqlQueryModel(this);
    objTableQuery->setQuery(Query);
    if (!objTable ->select())
    {
        qDebug()<<objTable->lastError().databaseText();
        qDebug()<<objTable ->lastError().driverText();
        return false;
    }else {

    completer->setModel(objTableQuery);
    return true;
    }
}

void DataBase::DiapasonDate(QTableView *tableView,QString TableName, QDateEdit *Date1, QDateEdit *Date2)
{
  objTable ->setTable(TableName);
  objTable->setFilter("Дата BETWEEN #" + Date1->text() + "# AND #"+ Date2->text() +"#");
  if (!objTable ->select())
  {
      qDebug()<<objTable->lastError().databaseText();
      qDebug()<<objTable ->lastError().driverText();
  }else tableView->setModel(objTable);
}

void DataBase::setItemInTable(QStandardItemModel *table, QString Item, int Row,qint32 Column)
{
  table->setData(table->index(Row,Column),Item);
}

void DataBase::setItemInTable(QStandardItemModel *table, QString Item, int Row,qint32 Column, Qt::Alignment AlignmentFlag)
{
  table->setData(table->index(Row,Column), Item);
  table->item(Row,Column)->setTextAlignment(AlignmentFlag);
}

void DataBase::setItemInTable(QStandardItemModel *table, qint32 Item, int Row,qint32 Column)
{
  table->setData(table->index(Row,Column),Item);
}

void DataBase::setItemInTable(QStandardItemModel *table, qreal Item, int Row,qint32 Column)
{
  table->setData(table->index(Row,Column),Item);
}

bool DataBase::setComboBox(QComboBox *ComboBoxView,QString TableName, qint32 ColumTable)
{
    qDebug()<<ComboBoxView;
    objTable = new QSqlTableModel(this);
    objTable ->setTable(TableName);
    if (!objTable ->select())
    {
        qDebug()<<objTable->lastError().databaseText();
        qDebug()<<objTable ->lastError().driverText();
        return false;
    }else {
    ComboBoxView->setModel(objTable);
    ComboBoxView->setModelColumn(ColumTable);
    return true;
    }
}


QSqlTableModel *DataBase::getObjTable()
{
  return objTable;
}


