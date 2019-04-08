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



QPair<QString, QString> itemValues[] = {
    {"id", "商品号"},
    {"name", "商品名"},
    {"costPrice", "入库单价"},
    {"itemCount", "商品数量"},
    {"sumValue", "总价"},
    {"note","备注"}
};


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

//DBManager::DBManager(QWidget *parent)
//{
    //connectDB();
    //createTable();

    //QSqlDatabase db = dataBase(DBCONNECTIONNAME);
    //m_model = new QSqlTableModel(this, db);
    //m_model->setTable(DBTableNAME);
    //m_model->select();
    //m_tableView = ui->tableView;
    //m_tableView->setModel(m_model);


    //m_model->setHeaderData(0, Qt::Horizontal, itemValues[0].second);
    //m_model->setHeaderData(1, Qt::Horizontal, itemValues[1].second);
    //m_model->setHeaderData(2, Qt::Horizontal, itemValues[2].second);
    //m_model->setHeaderData(3, Qt::Horizontal, itemValues[3].second);
    //m_model->setHeaderData(4, Qt::Horizontal, itemValues[4].second);

    //connect(m_model, &QSqlTableModel::dataChanged, this, &DBManager::setSumPrice);
//}

/**
 * @brief 创建数据库
 * 数据库写死的
 * @return 是否成功
 */
bool DBManager::createDB()
{
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

    if (query.exec(createCommand))
    {
        if (query.exec(commands::selectAllSql))
        {
            return true;
        }
    }

    QString errorString("table InputStorage already exists Unable to execute statement");
    if (query.lastError().text() == errorString)
    {
        return true;
    }

    return false;
}

QSqlDatabase DBManager::database()
{
    return mainDB;
}

DBManager::DBManager(QObject *parent)
    :QObject(parent)
{
}

QSqlDatabase DBManager::mainDB;

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
//
//void DBManager::setSumPrice(const QModelIndex &topLeft, const QModelIndex &bottomRight)
//{
//   // Q_ASSERT_X(topLeft == bottomRight, "SUM_PRICE！", "do not change SUM_PRICE");
//    float costValue, itemCount;
//
//    if (topLeft.column() == 2)
//    {
//        costValue = topLeft.data().toFloat();
//        itemCount = topLeft.sibling(topLeft.row(), topLeft.column() + 1).data().toInt();
//    }
//    else if (topLeft.column() == 3)
//    {
//        costValue = topLeft.sibling(topLeft.row(), topLeft.column() - 1).data().toFloat();
//        itemCount = topLeft.data().toInt();
//    }
//    else
//    {
//        return;
//    }
//
//    float sumValue = costValue * itemCount;
//    QModelIndex sumIndex = topLeft.sibling(topLeft.row(), ui->tableView->model()->columnCount() - 1);
//
//    m_model->setData(sumIndex, sumValue);
//}
