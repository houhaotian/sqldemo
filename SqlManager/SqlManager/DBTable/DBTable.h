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

    DBTable(QWidget *parent = Q_NULLPTR);
    ~DBTable();

    bool createTable(TableType m_type);

public slots:
    bool insertIndex();
    bool removeIndex();

private:
    Ui::DBTable *ui;
    QTableView *m_tableView;
    QSqlTableModel *m_model;
};
