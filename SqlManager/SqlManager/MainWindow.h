#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class InputTable;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

private slots:
    void on_insertButton_clicked();
    void on_deleteButton_clicked();

private:
    Ui::MainWindow *ui;

    InputTable *inputTable;
};
