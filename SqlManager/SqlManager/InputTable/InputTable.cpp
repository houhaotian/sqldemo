#include "InputTable.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include "SqlPlugin/DBManager.h"
#include <QMessageBox>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlRecord>


#define INPUTTABLENAME "InputStorage"
#pragma execution_character_set("utf-8")

QList<QPair<QString, QString>> itemValues = {
    {"itemId", "商品号"},
    {"name", "商品名"},
    {"costPrice", "入库单价"},
    {"itemCount", "商品数量"},
    {"sumValue", "总价"},
    {"note", "备注"}
};

namespace INPUT_COMMANDS
{
    //-----------------------------------------表名称---------------------------------ID--------NAME--------入库单价----数量----总价-----备注
    QString createTable = QString("create table %1 (id INTEGER PRIMARY KEY AUTOINCREMENT, %2 int, %3 varchar(30), %4 REAL, %5 int, %6 REAL,%7 TEXT)")
        .arg(INPUTTABLENAME,
            itemValues[0].first,
            itemValues[1].first,
            itemValues[2].first,
            itemValues[3].first,
            itemValues[4].first,
            itemValues[5].first);
};

InputTable::InputTable(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InputTable)
{
    ui->setupUi(this);

    if (!DBManager::createDB())
    {
        QMessageBox::warning(this, "warning", QStringLiteral("数据库连接失败！"));
        return;
    }
    if (!DBManager::createTable(INPUT_COMMANDS::createTable))
    {
        QMessageBox::warning(this, "warning", QStringLiteral("入库表不存在！"));
        return;
    }

    QSqlDatabase db = DBManager::database();

    m_model = new QSqlTableModel(this, db);
    m_model->setTable(INPUTTABLENAME);
    m_model->select();
    m_tableView = ui->tableView;
    m_tableView->setModel(m_model);


    for (int i = 0; i < itemValues.size(); i++) {
        m_model->setHeaderData(i, Qt::Horizontal, itemValues[i].second);
    }

    //connect(m_model, &QSqlTableModel::dataChanged, this, &DBManager::setSumPrice);
}

InputTable::~InputTable()
{
}


bool InputTable::insertIndex()
{
    auto record = m_model->record();
    int rowCount = m_model->rowCount();
    record.setValue(0, rowCount + 1);
    return m_model->insertRecord(rowCount, record);
}