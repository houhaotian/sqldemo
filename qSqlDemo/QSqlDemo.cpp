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

# pragma execution_character_set("utf-8")


QPair<QString, QString> itemValues[] = {
    {"id", "商品号"},
    {"name", "商品名"},
    {"costPrice", "入库单价"},
    {"itemCount", "商品数量"},
    {"sumValue", "总价"},
};

namespace commands
{
    QString createTable = QString("create table %1 (%2 int primary key, %3 varchar(30), %4 int,%5 int, %6 int)")
        .arg(DBTableNAME,
        itemValues[0].first,
        itemValues[1].first,
        itemValues[2].first,
        itemValues[3].first,
        itemValues[4].first);

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
    m_model = new QSqlTableModel(this, db);
    m_model->setTable(DBTableNAME);
    m_model->select();
    m_tableView = ui->tableView;
    m_tableView->setModel(m_model);


    m_model->setHeaderData(0, Qt::Horizontal, itemValues[0].second);
    m_model->setHeaderData(1, Qt::Horizontal, itemValues[1].second);
    m_model->setHeaderData(2, Qt::Horizontal, itemValues[2].second);
    m_model->setHeaderData(3, Qt::Horizontal, itemValues[3].second);
    m_model->setHeaderData(4, Qt::Horizontal, itemValues[4].second);

    connect(m_model, &QSqlTableModel::dataChanged, this, &QSqlDemo::setSumPrice);
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
    auto record = m_model->record();
    int rowCount = m_model->rowCount();
    record.setValue(0, rowCount + 1);
    bool ret = m_model->insertRecord(rowCount, record);
    qDebug() << "插入失败！" << ret;
}

void QSqlDemo::on_aboutButton_clicked()
{
    QString info = QStringLiteral("    商品号是唯一的，我还没有做输入限制，因此你要确保输入的货号是唯一的否则第二个重复货号的商品信息无法录入。\n");
    info.append(QStringLiteral("    单价数量总价只能输入数字，若输入其他字符会无法录入，我也没做限制，下次再做。"));

    QMessageBox::information(this, "warning", info);
}

void QSqlDemo::setSumPrice(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
   // Q_ASSERT_X(topLeft == bottomRight, "SUM_PRICE！", "do not change SUM_PRICE");
    int costValue, itemCount;

    if (topLeft.column() == 2)
    {
        costValue = topLeft.data().toInt();
        itemCount = topLeft.sibling(topLeft.row(), topLeft.column() + 1).data().toInt();
    }
    else if (topLeft.column() == 3)
    {
        costValue = topLeft.sibling(topLeft.row(), topLeft.column() - 1).data().toInt();
        itemCount = topLeft.data().toInt();
    }
    else
    {
        return;
    }

    int sumValue = costValue * itemCount;
    QModelIndex sumIndex = topLeft.sibling(topLeft.row(), ui->tableView->model()->columnCount() - 1);

    m_model->setData(sumIndex, sumValue);
}
