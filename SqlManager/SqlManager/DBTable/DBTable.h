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
    virtual ~DBTable();

    bool createTable(TableType m_type);

public slots:
    bool insertIndex();
    bool removeIndex();

private slots :
    void on_insertButton_clicked();
    void on_deleteButton_clicked();

private:
    Ui::DBTable *ui;
    QTableView *m_tableView;
    QSqlTableModel *m_model;
};
