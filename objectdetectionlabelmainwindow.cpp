#include "objectdetectionlabelmainwindow.h"
#include "ui_objectdetectionlabelmainwindow.h"

ObjectDetectionLabelMainWindow::ObjectDetectionLabelMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ObjectDetectionLabelMainWindow)
{
    ui->setupUi(this);
}

ObjectDetectionLabelMainWindow::~ObjectDetectionLabelMainWindow()
{
    delete ui;
}

void ObjectDetectionLabelMainWindow::on_ExitBtn_clicked()
{
    send_returnInfo(2);
}
