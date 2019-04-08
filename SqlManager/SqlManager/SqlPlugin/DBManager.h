#pragma once

#include <QObject>
#include <QSqlDatabase>

class DBManager : public QObject
{
    Q_OBJECT

public:
    DBManager *instance() {
        static DBManager dbManager;
        return &dbManager;
    }

    static bool createDB();
    static bool createTable(QString createCommand);
    static QSqlDatabase database();


    //bool insertTest(char *name, int age);
   //-------------

private slots:
    /* void on_addButton_clicked();
     void on_aboutButton_clicked();
     void setSumPrice(const QModelIndex &topLeft, const QModelIndex &bottomRight);*/

private:
    Q_DISABLE_COPY(DBManager);
    DBManager(QObject *parent = 0);
  
private:
    static QSqlDatabase mainDB;
};
