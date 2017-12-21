#include "selectlabelmodelmainwindow.h"
#include "ui_selectlabelmodelmainwindow.h"

SelectLabelModelMainWindow::SelectLabelModelMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SelectLabelModelMainWindow)
{
    ui->setupUi(this);
    m_envir_window = new MainWindow;
    m_objectDetect_window = new ObjectDetectionLabelMainWindow;
    connect(m_envir_window,SIGNAL(send_returnInfo(int)),this,SLOT(accept_subwindow(int)));
    connect(m_objectDetect_window,SIGNAL(send_returnInfo(int)),this,SLOT(accept_subwindow(int)));
}

SelectLabelModelMainWindow::~SelectLabelModelMainWindow()
{
    delete ui;
}

void SelectLabelModelMainWindow::accept_subwindow(int window_arg)
{
    switch (window_arg) {
    case 1:
        m_envir_window->close();
        this->show();
        break;
    case 2:
        m_objectDetect_window->close();
        this->show();
        break;
    default:
        break;
    }
}

void SelectLabelModelMainWindow::on_EnvironmentBtn_clicked()
{
    m_envir_window->show();
    this->close();
}

void SelectLabelModelMainWindow::on_ObjectDertectionBtn_clicked()
{
    m_objectDetect_window->show();
    this->close();
}
