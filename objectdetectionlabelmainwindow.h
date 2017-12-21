#ifndef OBJECTDETECTIONLABELMAINWINDOW_H
#define OBJECTDETECTIONLABELMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class ObjectDetectionLabelMainWindow;
}

class ObjectDetectionLabelMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ObjectDetectionLabelMainWindow(QWidget *parent = 0);
    ~ObjectDetectionLabelMainWindow();
signals:
    void send_returnInfo(int);
private slots:
    void on_ExitBtn_clicked();

private:
    Ui::ObjectDetectionLabelMainWindow *ui;
};

#endif // OBJECTDETECTIONLABELMAINWINDOW_H
