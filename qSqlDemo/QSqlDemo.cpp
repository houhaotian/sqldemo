#include "QSqlDemo.h"
#include <QSqlTableModel>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QSqlRecord>

#define DBCONNECTIONNAME "localSQL"
#define DBTableNAME "storage"
#define NAMELENGTH 30

QList<QString> values = {
    "name",         //商品名
    "costPrice",    //入库单价
    "itemCount",    //商品数量
    "sumValue"      //总价
};

namespace commands
{
    QString createTable = QString("create table %1 (id int primary key, %2 varchar(30), %3 int,%4 int, %5 int)")
        .arg(DBTableNAME, values[0], values[1], values[2], values[3]);
    QString selectMaxSql = QString("select max(id) from %1").arg(DBTableNAME);
    QString insertSql = QString("insert into %1 values (?, ?, ?)").arg(DBTableNAME);
    QString updateSql = QString("update %1 set name = :name where id = :id").arg(DBTableNAME);
    QString selectSql = QString("select id, name from %1").arg(DBTableNAME);
    QString selectAllSql = QString("select * from %1").arg(DBTableNAME);
    QString deleteSql = QString("delete from %1 where id = ?").arg(DBTableNAME);
    QString clearSql = QString("delete from %1").arg(DBTableNAME);
};



QSqlDemo::QSqlDemo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QSqlDemoClass)
{
    ui->setupUi(this);

    connectDB();
    createTable();

    QSqlDatabase db = dataBase(DBCONNECTIONNAME);
    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable(DBTableNAME);
    model->select();
    ui->tableView->setModel(model);

    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("商品号"));
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("商品名"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("入库单价"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("数量"));
    model->setHeaderData(4, Qt::Horizontal, QStringLiteral("总价"));

}

bool QSqlDemo::connectDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", DBCONNECTIONNAME);
    db.setDatabaseName(QString(DBTableNAME));
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
    QSqlDatabase db = dataBase(DBCONNECTIONNAME);
    QSqlQuery query(db);

    if (!query.exec(commands::createTable))
    {
        if (!query.exec(commands::selectAllSql))
        {
            QMessageBox::warning(this, "warning", QStringLiteral("数据库表创建失败！"));
            return false;
        }
    }

    QMessageBox::warning(this, "warning", QStringLiteral("数据库表创建成功！"));
    return true;
}

bool QSqlDemo::insertTest(char *name, int age)
{
    QSqlDatabase db = dataBase(DBCONNECTIONNAME);

    if (strlen(name) > NAMELENGTH)
    {
        return false;
    }

    QSqlQuery query(db);
    query.prepare(commands::selectMaxSql.toLatin1());

    int maxId;
    if (!query.exec())
    {
        qDebug() << query.lastError();
    }
    else
    {
        while (query.next())
        {
            maxId = query.value(0).toInt();
        }
    }

    query.prepare(commands::insertSql);
    query.addBindValue(maxId + 1);
    query.addBindValue(QString::fromLocal8Bit(name));
    query.addBindValue(age);

    if (query.exec())
    {
        QMessageBox::warning(this, "warning", QStringLiteral("插入成功！"));
        return true;
    }
    else
    {
        QMessageBox::warning(this, "warning", QStringLiteral("插入失败！"));
        return false;
    }
}

QSqlDatabase QSqlDemo::dataBase(QString DBName)
{
    return QSqlDatabase::database(DBName); //建立数据库连接
}


void QSqlDemo::on_addButton_clicked()
{
    auto model = qobject_cast<QSqlTableModel *>(ui->tableView->model());
    auto record = model->record();
    int rowCount = model->rowCount();
    record.setValue(0, rowCount + 1);
    qDebug() << model->insertRecord(rowCount, record);
}
