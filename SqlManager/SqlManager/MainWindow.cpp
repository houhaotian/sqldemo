#include "MainWindow.h"
#include "InputTable.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    inputTable = new InputTable(this);

    ui->horizontalLayout->addWidget(inputTable);
}

void MainWindow::on_insertButton_clicked()
{
    inputTable->insertIndex();
}

void MainWindow::on_deleteButton_clicked()
{
    inputTable->removeIndex();
}