/**************************************************************************************************************************
**		
**	Copyright:houhaotian
**	
**	file DBTable.cpp
**	
**	Author: Houhaotian
**	
**	Date: 2019/04/12
**
**	Description:作为table的工厂类。可以new入库，出库table。随new随用。
**              里面封装了tableView和SqlModel
**
**************************************************************************************************************************/
#include "DBTable.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include "SqlPlugin/DBManager.h"
#include <QMessageBox>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlRecord>
#include <QDateTime>

#include <QDebug>

#define INPUTTABLENAME "InputStorage"
#define OUTPUTTABLENAME "OutputStorage"
#pragma execution_character_set("utf-8")


namespace COMMANDS
{
    QList<QPair<QString, QString>> itemValues = {
        {"itemId", "商品号"},
        {"name", "商品名"},
        {"costPrice", "入库单价"},
        {"count", "商品数量"},
        {"sumPrice", "总价"},
        {"note", "备注"},
        {"dateTime", "日期"}
    };

    QString createTable = QString("create table %1 (id INTEGER PRIMARY KEY AUTOINCREMENT, \
        %2 int, %3 varchar(30), %4 REAL, %5 int, %6 REAL, %7 TEXT, %8 DATETIME)");

    QString constructCreateSQL(const QString &TableName) {
        QString createSQL = QString(createTable).arg(TableName);

        for (int i = 0; i < itemValues.size(); i++) {
            createSQL = QString(createSQL).arg(itemValues[i].first);
        }
        return createSQL;
    }
};

DBTable::DBTable(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DBTable)
{
    ui->setupUi(this);

    if (!DBManager::createDB())
    {
        QMessageBox::warning(this, "warning", "数据库连接失败！");
        return;
    }

    //connect(m_model, &QSqlTableModel::dataChanged, this, &DBManager::setSumPrice);
}

DBTable::~DBTable()
{
}

bool DBTable::createTable(TableType m_type)
{
    QString createSQL, m_tableName;
    if (m_type == TableType::input) {
        COMMANDS::itemValues[2].second = "入库单价";
        m_tableName = INPUTTABLENAME;
    }
    else if (m_type == TableType::output) {
        COMMANDS::itemValues[2].second = "出库单价";
        m_tableName = OUTPUTTABLENAME;
    }
    else {
        return false;
    }

    createSQL = COMMANDS::constructCreateSQL(m_tableName);

    if (!DBManager::createTable(createSQL))
    {
        QMessageBox::warning(this, "warning", "表创建失败！");
        return;
    }

    QSqlDatabase db = DBManager::database();

    m_model = new QSqlTableModel(this, db);
    m_model->setTable(m_tableName);
    m_model->select();
    m_tableView = ui->tableView;
    m_tableView->setModel(m_model);

    m_tableView->hideColumn(0);
    for (int i = 0; i < COMMANDS::itemValues.size(); i++) {
        m_model->setHeaderData(i + 1, Qt::Horizontal, COMMANDS::itemValues[i].second);
    }
    return true;
}

bool DBTable::insertIndex()
{
    auto record = m_model->record();
    int rowCount = m_model->rowCount();
    record.setValue(0, rowCount + 1);
    record.setValue(7, QDateTime::currentDateTime().toString(QString("yyyy/M/d H:mm:ss")));

    return m_model->insertRecord(rowCount, record);
}

bool DBTable::removeIndex()
{
    QModelIndex currentIndex = m_tableView->currentIndex();
    m_model->removeRow(currentIndex.row());
    m_model->select();
    return true;
}
