#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QDebug>
#include <QFileDialog>
#include <QSql>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QtWidgets>
#include <QStandardItemModel>
#include <QCompleter>

class CountAndValue
{
private:
  qint32 Count;
  qint32 Value;
public:
  CountAndValue(){Count=0;Value=0;};
  qint32 getCount() const{return Count;};
  void setCount(const qint32 &value){Count=value;};
  void incCount(const qint32 &value){Count+=value;};
  qint32 getValue() const{return Value;};
  void setValue(const qint32 &value){Value=value;};
  void incValue(const qint32 &value){Value+=value;};
};



  class DataBase : public QObject
  {
  Q_OBJECT
  public:
  explicit DataBase(QObject *parent = 0);
    bool CreatConection(QString NameDataBase);

    QSqlDatabase *getObjMDB();
    void setObjMDB(QSqlDatabase &value);

    QSqlQuery *QueryMDB(QString Query);
    QSqlQuery *getQueryMDB();

    QSqlTableModel *getObjTable();
    void setObjTable(QSqlTableModel &value);


    /*Иницализация Таблицы бд*/
    bool setTable(QTableView *tableView, QString TableName);
    /*Иницализация Таблицы бд c помощью SQL запроса*/
    bool setTableQuery(QTableView *tableView, QString TableName, QString NameProduct);
    bool setTableQuery(QTableView *tableView, QString Query);
    /*Заполнение элементов*/
    void setItemInBase(QVariant nameTable, QVariant item, QVariant cost, QVariant count, QDate date,QVariant Client);
    void setItemInTable(QStandardItemModel *table, QString Item,qint32 Row,qint32 Column);
    void setItemInTable(QStandardItemModel *table, QString Item, qint32 Row,qint32 Column, Qt::Alignment AlignmentFlag);
    void setItemInTable(QStandardItemModel *table, qint32 Item,qint32 Row,qint32 Column);
    void setItemInTable(QStandardItemModel *table, qreal Item,qint32 Row,qint32 Column);
    /*Запрос количество элементов в таблице*/
    qint32 getItemCount(QString TableName);
    /*Взять элемент из таблицы*/
    QString getItemProduct(QString TableName, qint32 Row);

    /*Взять диапозон по датам*/
    void DiapasonDate(QTableView *tableView, QString TableName, QDateEdit *Date1, QDateEdit *Date2);
    void DiapasonDate(QTableView *tableView,QString TableName, QDateEdit *Date1);

    /**/
    qint32 Profit(QTableView *table, qint32 iterator);

    qint32 SetCountAndValueItems(QTableView *table, QString ItemTable,
                                 QStandardItemModel *model, QString ItemsName,
                                 qint32 Row, qint32 Column);
    qint32 SetCountAndValueMidleItems(QTableView *table,QTableView *tableDown,
                                    QString ItemTable,QStandardItemModel *model,
                                    QString ItemsName,qint32 Row, qint32 Column);
    void SetCountAndValueFinalItems(QTableView *table,QStandardItemModel *model, qint32 Row,qint32 Column);


    /*Запрос данных из БД*/
    QSqlQuery *getQueryData();
    int SearchSQL(QString QuerySearch, QString indexOf);



    bool setCompleter(QCompleter *completer, QString Query);


    CountAndValue CountAndValueItems(QAbstractItemModel *tableView, QString ItemsName, QString ItemTable);
    CountAndValue CountAndValueMidleItems(QAbstractItemModel *tableView,QAbstractItemModel *table, QString ItemsName,QString ItemTable,qint32 iterator);
    CountAndValue CountAndValueFinalItems(QAbstractItemModel *table, qint32 Column);


    /*Работа с ComboBox'ами*/
    bool setComboBox(QComboBox *ComboBoxView, QString TableName, qint32 ColumTable, QSharedPointer<QSqlTableModel> &Table);



  signals:

  private:
    QSqlDatabase objDatabase;
    QSqlQuery objQueryMDB;
    QSqlTableModel *objTable;
    QSqlQueryModel *objTableQuery;


    CountAndValue Delivery_statistics;//Поставка
    CountAndValue Sales_statistics;//Продажа
    CountAndValue InitialBalance_statistics;
    // QSqlRecord RecordMDB;

public slots:
};

#endif // DATABASE_H
