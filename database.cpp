#include "database.h"
#include "mainwindow.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

bool DataBase::CreatConection(QString NameDataBase = "")
{
    objMDB = QSqlDatabase::addDatabase("QMYSQL");// Microsoft Access
    objMDB.setDatabaseName(NameDataBase);
       objMDB.setHostName("127.0.0.1");
       objMDB.setPort(3306);
       objMDB.setUserName("hays");
       objMDB.setPassword("hays");

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

bool DataBase::setTableQuery(QTableView *tableView)
{
      qDebug()<<tableView;
      objTableQuery = new QSqlQueryModel(this);
      QString Query;
      Query.append("SELECT \
                   `librarydb`.`books`.id_books,\
                   `librarydb`.`books`.name_book,\
                   `librarydb`.`books`.index_udc,\
                   `librarydb`.`books`.index_bbk,\
                   `librarydb`.`books`.isbn,\
                   GROUP_CONCAT(DISTINCT `librarydb`.`autor`.autor_record),\
                   GROUP_CONCAT(DISTINCT `librarydb`.`genre`.genre_record),\
                   GROUP_CONCAT(DISTINCT `librarydb`.`description`.description_record)\
               FROM\
                   `librarydb`.`books`\
                       JOIN\
                   `librarydb`.`autor_join_table` ON `librarydb`.`autor_join_table`.id_books = `librarydb`.`books`.id_books\
                       JOIN\
                   `librarydb`.`autor` ON `librarydb`.`autor`.id_autor = `librarydb`.`autor_join_table`.id_autor\
                       JOIN\
                   `librarydb`.`genre_join_table` ON `librarydb`.`genre_join_table`.id_books = `librarydb`.`books`.id_books\
                       JOIN\
                   `librarydb`.`genre` ON `librarydb`.`genre`.id_genre = `librarydb`.`genre_join_table`.id_genre\
                       JOIN\
                   `librarydb`.`description` ON `librarydb`.`description`.id_description = `librarydb`.`books`.id_books\
               GROUP BY `librarydb`.`books`.id_books;");
      objTableQuery->setQuery(Query);
      tableView->setModel(objTableQuery);
      //qDebug()<<tableView->model()->columnCount();
      //qDebug()<<Query;
      tableView->show();
      return true;
}

bool DataBase::setTableQuery(QTableView *tableView,QString TableName,QString NameProduct)
{
      qDebug()<<tableView;
      objTableQuery = new QSqlQueryModel(this);
      QString Query;
      Query.append("SELECT [Кол-во],[Дата] FROM Sales_statistics ");
      Query.append("WHERE ([Дата] BETWEEN #01/01/1970# AND #01/01/2070#) ");
      Query.append("AND ([Номенклатура товара]='"+NameProduct+"') ORDER BY [Дата]");

      objTableQuery->setQuery(Query);
      objTableQuery->setHeaderData(0, Qt::Horizontal, tr("Кол-во"));
      objTableQuery->setHeaderData(1, Qt::Horizontal, tr("Дата"));
      tableView->setModel(objTableQuery);
      qDebug()<<tableView->model()->columnCount();
      qDebug()<<Query;
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

void DataBase::DiapasonDate(QTableView *tableView,QString TableName, QDateEdit *Date1)
{
  objTable ->setTable(TableName);
  objTable->setFilter("Дата < #" + Date1->text() + "#");
  if (!objTable ->select())
  {
      qDebug()<<objTable->lastError().databaseText();
      qDebug()<<objTable ->lastError().driverText();
  }else tableView->setModel(objTable);
}

qint32 DataBase::Profit(QTableView *table, qint32 iterator)
{
    qint32 Sales = table->model()->data(table->model()->index(iterator,2),Qt::DisplayRole).toInt();
    qint32 CostPrice = table->model()->data(table->model()->index(iterator,3),Qt::DisplayRole).toInt();
    return Sales-CostPrice;
}


qint32 DataBase::SetCountAndValueItems(QTableView *table, QString ItemTable,
                                     QStandardItemModel *model, QString ItemsName,
                                     qint32 Row, qint32 Column)
{
  CountAndValue CountItemProduct = CountAndValueItems(table->model(),ItemsName,ItemTable);
  setItemInTable(model,CountItemProduct.getCount(),Row,Column);
  setItemInTable(model,CountItemProduct.getValue(),Row,Column+1);
  return CountItemProduct.getValue();
}

qint32 DataBase::SetCountAndValueMidleItems(QTableView *table,QTableView *tableDown, QString ItemTable, QStandardItemModel *model, QString ItemsName, qint32 Row, qint32 Column)
{
  CountAndValue CountItemProduct = CountAndValueMidleItems(table->model(),tableDown->model(),ItemsName,ItemTable,Row);
  setItemInTable(model,CountItemProduct.getCount(),Row,Column);
  setItemInTable(model,CountItemProduct.getValue(),Row,Column+1);
  return CountItemProduct.getValue();
}

void DataBase::SetCountAndValueFinalItems(QTableView *table,QStandardItemModel *model, qint32 Row,qint32 Column)
{
  CountAndValue CountItemProduct = CountAndValueFinalItems(table->model(),Row);
  setItemInTable(model,CountItemProduct.getCount(),Row,Column);
  setItemInTable(model,CountItemProduct.getValue(),Row,Column+1);
}

CountAndValue DataBase::CountAndValueItems(QAbstractItemModel *tableView, QString ItemsName,QString ItemTable)
{
  qint32 ItemCount = getItemCount(ItemTable);
  CountAndValue returedValue;

  for (qint32 iterator(0);iterator<ItemCount;iterator++)
    {
      if(tableView->data(tableView->index(iterator,1),Qt::DisplayRole).toString()==ItemsName)
        {
          returedValue.incCount(tableView->data(tableView->index(iterator,2),Qt::DisplayRole).toInt());
          returedValue.incValue(tableView->data(tableView->index(iterator,3),Qt::DisplayRole).toInt()*
                                tableView->data(tableView->index(iterator,2),Qt::DisplayRole).toInt());
        }
    }
  return returedValue;
}

CountAndValue DataBase::CountAndValueMidleItems(QAbstractItemModel *tableView,QAbstractItemModel *table, QString ItemsName,QString ItemTable,qint32 iterator)
{
  qint32 ItemCount = getItemCount(ItemTable);
  CountAndValue returedValue;

  for (qint32 iterator(0);iterator<ItemCount;iterator++)
    {
      if(tableView->data(tableView->index(iterator,1),Qt::DisplayRole).toString()==ItemsName)
        {
          returedValue.incCount(tableView->data(tableView->index(iterator,2),Qt::DisplayRole).toInt());
        }
    }


  qint32 InitialBalanceAndDelivery = table->data(table->index(iterator,2),Qt::DisplayRole).toInt() +
                                     table->data(table->index(iterator,4),Qt::DisplayRole).toInt();
  qint32 TotalDeliveryItem = table->data(table->index(iterator,1),Qt::DisplayRole).toInt() +
                             table->data(table->index(iterator,3),Qt::DisplayRole).toInt();
  if(!((InitialBalanceAndDelivery==0)or(TotalDeliveryItem==0)))
    {
      returedValue.setValue((InitialBalanceAndDelivery/TotalDeliveryItem)*returedValue.getCount());
    }else returedValue.setValue(0);
  return returedValue;
}

CountAndValue DataBase::CountAndValueFinalItems(QAbstractItemModel *tableView,qint32 iterator)
{
  CountAndValue returedValue;
  CountAndValue Delivery_statistics;//Поставка
  CountAndValue Sales_statistics;//Продажа
  CountAndValue InitialBalance_statistics;

  InitialBalance_statistics.setCount(tableView->data(tableView->index(iterator,1),Qt::DisplayRole).toInt());
  InitialBalance_statistics.setValue(tableView->data(tableView->index(iterator,2),Qt::DisplayRole).toInt());

  Delivery_statistics.setCount(tableView->data(tableView->index(iterator,3),Qt::DisplayRole).toInt());
  Delivery_statistics.setValue(tableView->data(tableView->index(iterator,4),Qt::DisplayRole).toInt());

  Sales_statistics.setCount(tableView->data(tableView->index(iterator,5),Qt::DisplayRole).toInt());
  Sales_statistics.setValue(tableView->data(tableView->index(iterator,6),Qt::DisplayRole).toInt());

  returedValue.incCount((InitialBalance_statistics.getCount()+Delivery_statistics.getCount())-Sales_statistics.getCount());
  returedValue.incValue((InitialBalance_statistics.getValue()+Delivery_statistics.getValue())-Sales_statistics.getValue());

  return returedValue;
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


