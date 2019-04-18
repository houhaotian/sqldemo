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

    ui->tabWidget->addTab(new QWidget, QStringLiteral("���"));
    ui->tabWidget->addTab(m_inputMenu, QStringLiteral("��ⵥ"));
    ui->tabWidget->addTab(new QWidget, QStringLiteral("���ⵥ"));

    ui->tabWidget->addTab(m_inputTable, QStringLiteral("����¼"));
    ui->tabWidget->addTab(m_outputTable, QStringLiteral("�����¼"));

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
