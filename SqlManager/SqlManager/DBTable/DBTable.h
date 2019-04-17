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
    DBTable(QWidget *parent = Q_NULLPTR);
    virtual ~DBTable();

    bool createTable(QString createSQL);

    const QString &tableName() const { return m_tableName; }
    void setTableName(QString val) { m_tableName = val; }

   QSqlTableModel * model() const { return m_model; }

public slots:
    void testFoo();

private slots :
    void on_insertButton_clicked();
    void on_deleteButton_clicked();
    bool insertIndex();
    bool removeIndex();


private:
    void setModel(QSqlTableModel *model) { m_model = model; }

private:
    Ui::DBTable *ui;
    QTableView *m_tableView;
    QSqlTableModel *m_model;
    QString m_tableName;

};
