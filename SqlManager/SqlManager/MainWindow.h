#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "DBTable.h"

class InputMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QScopedPointer<DBTable> m_inputTable, m_outputTable;
    InputMenu *m_inputMenu;
};
