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
    m_inputMenu = new InputMenu();

    ui->tabWidget->addTab(new QWidget, QStringLiteral("库存"));
    ui->tabWidget->addTab(m_inputMenu, QStringLiteral("入库单"));
    ui->tabWidget->addTab(new QWidget, QStringLiteral("出库单"));

    ui->tabWidget->addTab(m_inputTable, QStringLiteral("入库记录"));
    ui->tabWidget->addTab(m_outputTable, QStringLiteral("出库记录"));

    connect(m_inputMenu, &InputMenu::editInputMenu, qobject_cast<InputTable *>(m_inputTable), &InputTable::setInputMenuNumber);
    connect(m_inputMenu, &InputMenu::editInputMenu, [this] {
        ui->tabWidget->setCurrentIndex(3);
    });
}

void MainWindow::on_pushButton_clicked()
{
    m_inputTable->testFoo();
    m_outputTable->testFoo();
}
