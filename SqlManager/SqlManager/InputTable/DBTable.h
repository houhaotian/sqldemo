#pragma once

#include <QWidget>
#include "ui_DBTable.h"

class QTableView;
class QSqlTableModel;

class DBTable : public QWidget
{
    Q_OBJECT

public:

    enum TableType{
    input,
    output
    };

    DBTable(TableType type = input, QWidget *parent = Q_NULLPTR);
    ~DBTable();

public slots:
    bool insertIndex();
    bool removeIndex();

private slots:
    void on_insertButton_clicked();
    void on_deleteButton_clicked();

private:
    Ui::DBTable *ui;
    QTableView *m_tableView;
    QSqlTableModel *m_model;
    TableType m_type;
    QString m_tableName;
};
