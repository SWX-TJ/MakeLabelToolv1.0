#ifndef SELECTLABELMODELMAINWINDOW_H
#define SELECTLABELMODELMAINWINDOW_H
#include <QMainWindow>
#include "mainwindow.h"
#include "objectdetectionlabelmainwindow.h"
namespace Ui {
class SelectLabelModelMainWindow;
}

class SelectLabelModelMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SelectLabelModelMainWindow(QWidget *parent = 0);
    ~SelectLabelModelMainWindow();

public:
    MainWindow *m_envir_window;
    ObjectDetectionLabelMainWindow *m_objectDetect_window;
public slots:
    void accept_subwindow(int);
private slots:
    void on_EnvironmentBtn_clicked();
    void on_ObjectDertectionBtn_clicked();

private:
    Ui::SelectLabelModelMainWindow *ui;
};

#endif // SELECTLABELMODELMAINWINDOW_H
