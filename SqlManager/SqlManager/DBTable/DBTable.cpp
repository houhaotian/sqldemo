/****************************************************************************
**		
**	Copyright:Mine
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
****************************************************************************/

#include "DBTable.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include "DBManager.h"
#include <QMessageBox>
#include <QTableView>
#include <QSqlRecord>
#include <QDateTime>

#include <QDebug>

#define INPUTMENU "inputMenu"
#define OUTPUTMENU "outputMenu"

#pragma execution_character_set("utf-8")

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

}

DBTable::~DBTable()
{
}

bool DBTable::createTable(QString createSQL)
{
    if (!DBManager::createTable(createSQL))
    {
        QMessageBox::warning(this, "warning", "表创建失败！");
        return false;
    }

    QSqlDatabase db = DBManager::database();

    setModel(new QSqlTableModel(this, db));
    model()->setTable(tableName());
    model()->select();
    m_tableView = ui->tableView;
    m_tableView->setModel(model());

    m_tableView->hideColumn(0);
    
    connect(m_tableView, &QTableView::customContextMenuRequested, this, &DBTable::showContextMenu);

    return true;
}

bool DBTable::insertIndex()
{
    auto record = model()->record();
    int rowCount = model()->rowCount();
    //record.setValue(0, rowCount + 1);
    record.setValue(7, QDateTime::currentDateTime().toString(QString("yyyy/M/d H:mm:ss")));

     model()->insertRecord(rowCount, record);
     return model()->select();
}

bool DBTable::removeIndex()
{
    QModelIndex currentIndex = m_tableView->currentIndex();
    model()->removeRow(currentIndex.row());
    return model()->select();
}

void DBTable::showContextMenu(const QPoint &pos)
{
    QModelIndex index = m_tableView->indexAt(pos);
    if (index.row() < 0)
        return;
    else
        contextMenuRequested(index);
}

void DBTable::on_insertButton_clicked()
{
    insertIndex();
}

void DBTable::on_deleteButton_clicked()
{
    removeIndex();
}


void DBTable::testFoo()
{
  /*  QString command1 = QString("SELECT * FROM %1 ORDER BY %2 ASC").arg(INPUTTABLENAME, COMMANDS::itemValues[0].first);
    QString command2 = QString("SELECT * FROM %1 ORDER BY %2 ASC").arg(OUTPUTTABLENAME, COMMANDS::itemValues[0].first);

    QSqlQuery query(DBManager::database());
    query.exec(command1);

    int count;
    float costPrice, sumPrice;

    while (query.next())
    {
       static int itemID = query.value(1).toInt();
       if (itemID != query.value(1).toInt())
       {
           costPrice = 0;
           count = 0;
           sumPrice = 0;
       }

        costPrice += query.value(3).toFloat();
        count += query.value(4).toInt();
        sumPrice += query.value(5).toFloat();
    }

    query.exec(command2);*/
}
