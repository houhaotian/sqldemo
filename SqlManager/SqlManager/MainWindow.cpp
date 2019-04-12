#include "MainWindow.h"
#include "DBTable.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_outputTable = new DBTable();
    m_inputTable = new DBTable();

    ui->tabWidget->addTab(m_inputTable, QStringLiteral("����¼"));
    ui->tabWidget->addTab(m_outputTable, QStringLiteral("�����¼"));

}
