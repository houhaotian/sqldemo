/**************************************************************************************************************************
**		
**	Copyright:Mine
**	
**	file DBTable.h
**	
**	Author: Houhaotian
**	
**	Date: 2019/04/17
**
**	Description:作为table的工厂类。可以new入库，出库table。随new随用。
**              里面封装了tableView和SqlModel
**
**************************************************************************************************************************/
#pragma once

#include <QWidget>
#include <QSqlTableModel>

#include "ui_DBTable.h"

class QTableView;
class QSqlTableModel;

class DBTable : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QString tableName READ tableName WRITE setTableName)

public:
    explicit DBTable(QWidget *parent = Q_NULLPTR);
    virtual ~DBTable();

    bool createTable(QString createSQL);
    QSqlTableModel * model() const { return m_model; }

    const QString &tableName() const { return m_tableName; }
    void setTableName(QString val) { m_tableName = val; }

public slots:
    void testFoo();
    virtual bool insertIndex();

private slots :
    void on_insertButton_clicked();
    void on_deleteButton_clicked();
    bool removeIndex();
    void showContextMenu(const QPoint &pos);
    virtual void contextMenuRequested(QModelIndex) {}

private:
    void setModel(QSqlTableModel *model) { m_model = model; }

private:
    Ui::DBTable *ui;
    QTableView *m_tableView;
    QSqlTableModel *m_model;
    QString m_tableName;

};
