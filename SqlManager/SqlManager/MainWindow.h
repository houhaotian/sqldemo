#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class DBTable;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    DBTable *m_inputTable, *m_outputTable;
};
