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

    ui->tabWidget->addTab(new QWidget, QStringLiteral("���"));
    ui->tabWidget->addTab(new InputMenu, QStringLiteral("��ⵥ"));
    ui->tabWidget->addTab(new QWidget, QStringLiteral("���ⵥ"));

    ui->tabWidget->addTab(m_inputTable, QStringLiteral("����¼"));
    ui->tabWidget->addTab(m_outputTable, QStringLiteral("�����¼"));

}

void MainWindow::on_pushButton_clicked()
{
    m_inputTable->testFoo();
    m_outputTable->testFoo();
}
