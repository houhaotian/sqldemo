#include "DBManager.h"
#include <QSqlTableModel>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QSqlRecord>


#define DBCONNECTIONNAME "localSQL"
#define DBNAME "Storage"
#define NAMELENGTH 30


namespace commands
{
    QString selectMaxSql = QString("select max(id) from %1");
    QString insertSql = QString("insert into %1 values (?, ?, ?)");
    QString updateSql = QString("update %1 set name = :name where id = :id");
    QString selectSql = QString("select id, name from %1");
    QString selectAllSql = QString("select * from %1");
    QString deleteSql = QString("delete from %1 where id = ?");
    QString clearSql = QString("delete from %1");
};

QSqlDatabase DBManager::mainDB;

QSqlDatabase DBManager::database()
{
    return mainDB;
}

DBManager::DBManager(QObject *parent)
    :QObject(parent)
{
}

/**
 * @brief 创建数据库
 * 数据库写死的
 * @return 是否成功
 */
bool DBManager::createDB()
{
    if (mainDB.isOpen())
        return true;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", DBCONNECTIONNAME);
    db.setDatabaseName(DBNAME);
    db.setUserName("houhaotian");
    db.setPassword("123456");
    db.setHostName("127.0.0.1");
    db.setPort(6000);
    // db.setConnectOptions();

    if (!db.open())
    {
        return false;
    }

    mainDB = db;
    return true;
}

/**
 * @brief 创建表
 * @param createCommand创建语句
 * @return 是否成功
 */
bool DBManager::createTable(QString createCommand)
{
    QSqlQuery query(database());
    query.clear();
    if (query.exec(createCommand))
    {
        if (query.exec(commands::selectAllSql))
        {
            return true;
        }
    }

    QString errorString("table * already exists Unable to execute statement");
    if (!query.lastError().text().contains( errorString, Qt::CaseSensitive))
    {
        qDebug() << query.lastError();
        return true;
    }

    qDebug() << query.lastError();
    return false;
}


//bool DBManager::insertTest(char *name, int age)
//{
//    QSqlDatabase db = dataBase(DBCONNECTIONNAME);
//
//    if (strlen(name) > NAMELENGTH)
//    {
//        return false;
//    }
//
//    QSqlQuery query(db);
//    query.prepare(commands::selectMaxSql.toLatin1());
//
//    int maxId;
//    if (!query.exec())
//    {
//        qDebug() << query.lastError();
//    }
//    else
//    {
//        while (query.next())
//        {
//            maxId = query.value(0).toInt();
//        }
//    }
//
//    query.prepare(commands::insertSql);
//    query.addBindValue(maxId + 1);
//    query.addBindValue(QString::fromLocal8Bit(name));
//    query.addBindValue(age);
//
//    if (query.exec())
//    {
//        QMessageBox::warning(this, "warning", QStringLiteral("插入成功！"));
//        return true;
//    }
//    else
//    {
//        QMessageBox::warning(this, "warning", QStringLiteral("插入失败！"));
//        return false;
//    }
//}

//
//void DBManager::on_addButton_clicked()
//{
//    auto record = m_model->record();
//    int rowCount = m_model->rowCount();
//    record.setValue(0, rowCount + 1);
//    bool ret = m_model->insertRecord(rowCount, record);
//    qDebug() << "插入失败！" << ret;
//}
//
//void DBManager::on_aboutButton_clicked()
//{
//    QString info = QStringLiteral("    商品号是唯一的，我还没有做输入限制，因此你要确保输入的货号是唯一的否则第二个重复货号的商品信息无法录入。\n");
//    info.append(QStringLiteral("    单价数量总价只能输入数字，若输入其他字符会无法录入，我也没做限制，下次再做。"));
//
//    QMessageBox::information(this, "warning", info);
//}
