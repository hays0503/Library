#include "database.h"
#include "mainwindow.h"
#include "queryfactory.h"
#include <iostream>
#include <QTextStream>

#include <QtConcurrent>
#include <QFutureWatcher>
#include <QFuture>

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

bool DataBase::CreatConection(QString NameDataBase = "")
{
    objDatabase = QSqlDatabase::addDatabase("QMYSQL");// Microsoft Access
    objDatabase.setDatabaseName(NameDataBase);
       objDatabase.setHostName("127.0.0.1");
       objDatabase.setPort(3306);
       objDatabase.setUserName("hays0503");
       objDatabase.setPassword("hays0503");

    if (objDatabase.open()) {
           qDebug("Success!");
           qDebug()<<objDatabase;
           return true;
    } else {
        qDebug()<<objDatabase.lastError().text();
        //qDebug()<<connectString;
        return false;
    }

}

QSqlDatabase *DataBase::getObjMDB()
{
    return &objDatabase;
}

void DataBase::setObjMDB(QSqlDatabase &value)
{
    objDatabase = value;
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

QSqlQuery *DataBase::getQueryData()
{
    QSqlQuery *p_QSqlQuery = new QSqlQuery(*this->getObjMDB());
    return p_QSqlQuery;
}

int DataBase::SearchSQL(QString QuerySearch, QString indexOf)
{
    int result = 0;
    QSqlQuery *p_QSqlQuery = new QSqlQuery(*this->getObjMDB());
    qDebug()<<QuerySearch;
    if (!p_QSqlQuery->exec(QuerySearch)) {
        qDebug() << "Unable to execute query - exiting";
    }else{
        QSqlRecord rec = p_QSqlQuery->record();
        p_QSqlQuery->next();
        result = p_QSqlQuery->value(rec.indexOf(indexOf)).toInt();
    }
    delete p_QSqlQuery;
    return result;
}

bool DataBase::setCompleter(QCompleter *completer, QString Query)
{
    QFuture<QSqlQueryModel*> future = QtConcurrent::run(
        [this,Query]()
        {
            objTableQuery = new QSqlQueryModel();
            objTableQuery->setQuery(Query);
            objTableQuery->query();
            return objTableQuery;
         });
    QFutureWatcher<QSqlQueryModel*> *watcher = new QFutureWatcher<QSqlQueryModel*>(this);
    connect(watcher,&QFutureWatcherBase::finished,[this, watcher,completer]()
    {// Запускаем этот код в UI потоке, когда объект future завершит свою работу в рабочем потоке
        completer->setModel(watcher->result());
        watcher->deleteLater(); // Удалим ненужный watcher
    });
     watcher->setFuture(future); // Связываем watcher с feature. Это быстрая операция и не тормозит поток UI

    return true;
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

bool DataBase::setComboBox(QComboBox *ComboBoxView,QString TableName, qint32 ColumTable, QSharedPointer<QSqlTableModel> &Table)
{

    QFuture<QSharedPointer<QSqlTableModel>> future = QtConcurrent::run(
        [this,TableName]()
        {
            objDatabase = QSqlDatabase::addDatabase("QMYSQL");
            objDatabase.setDatabaseName("librarydb");
            objDatabase.setHostName("127.0.0.1");
            objDatabase.setPort(3306);
            objDatabase.setUserName("hays0503");
            objDatabase.setPassword("hays0503");
            objDatabase.open();

            QSharedPointer<QSqlTableModel> p_Table = QSharedPointer<QSqlTableModel>(new QSqlTableModel);
            p_Table ->setTable(TableName);
            p_Table ->select();
            return p_Table;
         });

    QFutureWatcher<QSharedPointer<QSqlTableModel>> *watcher = new QFutureWatcher<QSharedPointer<QSqlTableModel>>(this);
    connect(watcher,&QFutureWatcherBase::finished,[watcher,ComboBoxView,ColumTable,&Table]() mutable
    {// Запускаем этот код в UI потоке, когда объект future завершит свою работу в рабочем потоке
        QSharedPointer<QSqlTableModel> Tables = watcher->result();
        Table = Tables;
        ComboBoxView->setModel(Table.data());
        ComboBoxView->setModelColumn(ColumTable);
        ComboBoxView->showPopup();
        //watcher->deleteLater(); // Удалим ненужный watcher
    });
    watcher->setFuture(future); // Связываем watcher с feature. Это быстрая операция и не тормозит поток UI
    return true;

}


QSqlTableModel *DataBase::getObjTable()
{
  return objTable;
}


