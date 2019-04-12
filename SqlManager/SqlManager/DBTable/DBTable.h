#pragma once

#include <QWidget>
#include "ui_DBTable.h"

class QTableView;
class QSqlTableModel;

class DBTable : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QString tableName READ tableName WRITE setTableName)

public:
    enum TableType{
    input,
    output
    };

    DBTable(QWidget *parent = Q_NULLPTR);
    virtual ~DBTable();

    bool createTable(TableType m_type);

    const QString &tableName() const { return m_tableName; }
    void setTableName(QString val) { m_tableName = val; }

public slots:
    void testFoo();


private slots :
    void on_insertButton_clicked();
    void on_deleteButton_clicked();
    bool insertIndex();
    bool removeIndex();

    void setSumPrice(const QModelIndex &topLeft, const QModelIndex &bottomRight);

private:

private:
    Ui::DBTable *ui;
    QTableView *m_tableView;
    QSqlTableModel *m_model;
    QString m_tableName;
};
