/**************************************************************************************************************************
**
**	Copyright:Mine
**
**	file DBManager.h
**
**	Author: Houhaotian
**
**	Date: 2019/04/17
**
**	Description:这个是操作数据库的基类。只提供了创建数据库，创建表的接口。
**
**************************************************************************************************************************/
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

private slots:
   

private:
    Q_DISABLE_COPY(DBManager)
    DBManager(QObject *parent = 0);
  
private:
    static QSqlDatabase mainDB;
};
