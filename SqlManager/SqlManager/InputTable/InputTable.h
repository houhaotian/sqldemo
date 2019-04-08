#pragma once

#include <QWidget>
#include "ui_InputTable.h"

class QTableView;
class QSqlTableModel;

class InputTable : public QWidget
{
    Q_OBJECT

public:
    InputTable(QWidget *parent = Q_NULLPTR);
    ~InputTable();

public slots:
    bool insertIndex();

private:
    Ui::InputTable *ui;
    QTableView *m_tableView;
    QSqlTableModel *m_model;
};
