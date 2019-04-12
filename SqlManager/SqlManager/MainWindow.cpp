#include "MainWindow.h"
#include "InputTable.h"
#include "OutputTable.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_outputTable = new InputTable();
    m_inputTable = new OutputTable();

    ui->tabWidget->addTab(m_inputTable, QStringLiteral("����¼"));
    ui->tabWidget->addTab(m_outputTable, QStringLiteral("�����¼"));

}
