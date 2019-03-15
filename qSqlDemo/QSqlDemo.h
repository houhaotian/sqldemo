#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QSqlDemo.h"
#include <QSqlDatabase>

class QTableView;
class QSqlTableModel;

class QSqlDemo : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDemo(QWidget *parent = Q_NULLPTR);

    bool connectDB();
    bool createTable();

    bool insertTest(char *name, int age);

private slots:
    void on_addButton_clicked();
    void on_aboutButton_clicked();
    void setSumPrice(const QModelIndex &topLeft, const QModelIndex &bottomRight);

private:
    QSqlDatabase dataBase(QString DBName);

private:
    Ui::QSqlDemoClass *ui;
    QTableView *m_tableView;
    QSqlTableModel *m_model;
};
