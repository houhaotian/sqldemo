#include "QSqlDemo.h"
#include <QSqlTableModel>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>

namespace commands
{
    QString createTable = "create table storage (id int primary key, name varchar(30), age int)";
    QString selectMaxSql = "select max(id) from storage";
    QString insertSql = "insert into storage values (?, ?, ?)";
    QString updateSql = "update storage set name = :name where id = :id";
    QString selectSql = "select id, name from storage";
    QString selectAllSql = "select * from storage";
    QString deleteSql = "delete from storage where id = ?";
    QString clearSql = "delete from storage";
};



QSqlDemo::QSqlDemo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QSqlDemoClass)
{
    ui->setupUi(this);

    connectDB();
    createTable();


//    QSqlTableModel *model = new QSqlTableModel(this, db);
}

bool QSqlDemo::connectDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "localSQL");
    db.setDatabaseName("storage");
    db.setUserName("houhaotian");
    db.setPassword("123456");
    db.setHostName("127.0.0.1");
    db.setPort(6000);
    // db.setConnectOptions();

    if (!db.open())
    {
        QMessageBox::warning(this, "warning", QStringLiteral("数据库打开失败"));
        return false;
    }
    return true;
}

bool QSqlDemo::createTable()
{
    QSqlDatabase db = QSqlDatabase::database("localSQL"); //建立数据库连接
    QSqlQuery query(db);

    query.prepare(commands::createTable);
    if (query.exec())
    {
        QMessageBox::warning(this, "warning", QStringLiteral("数据库表创建成功！"));
        return true;
    }
    else
    {
        QMessageBox::warning(this, "warning", QStringLiteral("数据库表创建失败！"));
        return false;
    }
}
//
////向数据库中插入记录
//bool QSqlDemo::insert()
//{
//    //QSqlDatabase db = QSqlDatabase::database("localSQL"); //建立数据库连接
//    //QSqlQuery query(db);
//    //query.prepare("insert into automobil values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
//
//    //long records = 10;
//    //for (int i = 0; i < records; i++)
//    //{
//    //    query.bindValue(0, i);
//    //    query.bindValue(1, "四轮");
//    //    query.bindValue(2, "轿车");
//    //    query.bindValue(3, "富康");
//    //    query.bindValue(4, rand() % 100);
//    //    query.bindValue(5, rand() % 10000);
//    //    query.bindValue(6, rand() % 300);
//    //    query.bindValue(7, rand() % 200000);
//    //    query.bindValue(8, rand() % 52);
//    //    query.bindValue(9, rand() % 100);
//
//    //    bool success = query.exec();
//    //    if (!success)
//    //    {
//    //        QSqlError lastError = query.lastError();
//    //        qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
//    //        return false;
//    //    }
//    //}
//    return true;
//}
