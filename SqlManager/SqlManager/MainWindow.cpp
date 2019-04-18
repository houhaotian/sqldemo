#include "MainWindow.h"
#include "InputTable.h"
#include "OutputTable.h"
#include "InputMenu.h"
#include <QDateTime>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    m_inputTable = new InputTable();
    m_outputTable = new OutputTable();

    ui->tabWidget->addTab(new QWidget, QStringLiteral("库存"));
    ui->tabWidget->addTab(new InputMenu, QStringLiteral("入库单"));
    ui->tabWidget->addTab(new QWidget, QStringLiteral("出库单"));

    ui->tabWidget->addTab(m_inputTable, QStringLiteral("入库记录"));
    ui->tabWidget->addTab(m_outputTable, QStringLiteral("出库记录"));

}

void MainWindow::on_pushButton_clicked()
{
    m_inputTable->testFoo();
    m_outputTable->testFoo();
}
