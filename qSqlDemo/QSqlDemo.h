#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QSqlDemo.h"

class QSqlDemo : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDemo(QWidget *parent = Q_NULLPTR);

    bool connectDB();
    bool createTable();

private:
    Ui::QSqlDemoClass *ui;
};
