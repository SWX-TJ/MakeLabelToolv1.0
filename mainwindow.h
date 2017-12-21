#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <opencv.hpp>
#include <imgprocthread.h>
#include <QFile>
#include <QFileInfo>
#include <QMouseEvent>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include <QKeyEvent>
#include <musicplayer.h>
using namespace cv;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public:
    QPoint leftPoint;
    QPoint rightPoint;
    QPoint leftFnishPoint;
    QPoint rightFnishPoint;
    Mat    OriImage;
    QImage DispImage;
    Mat TempleteImage;
    QImage tempDispImage;
    QPixmap pixmap;
    QString   File_INFO;
    QString   File_path;
    QString   File_name;
    QFileInfo File_info;
    QString selectSaveImgDir;
    int traing_TempleteImageNum;
    int testing_TempleteImageNum;
    ImgProcThread *m_makeimg;
    MusicPlayer    *m_player;
    QVector<QString>TrainingLabelIndex;
    QVector<int>TrainingLabelIndexLastnum;
    QVector<QString>TestingLabelIndex;
    QVector<int>TestingLabelIndexLastnum;
    QFile trainingFileList;
    QFile  testingFileList;
    QString neededLabelImageFilePath;
     QList<QFileInfo> *neededLabelImageFileInfo;
      int neededLabelImageNum;
      int neededLabelImgIndex;
public:
    bool isLeftPoint;
    bool isRightPoint;
    bool isLeftPointFinish;
    bool isRightPointFinish;
    bool isfirstSelect;
    bool isbinaryClassfiy;
public:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent  *event);
public:
     QImage convertMatToQImage(Mat &mat);
     Mat   convertQImageToMat(QImage &image);
     bool isDirexits(QString filedir);
private slots:
    void on_ExitBtn_clicked();
    void on_InsertNewLabelBtn_clicked();
    void on_deteCurrentLabelBtn_clicked();
    void on_DeleteAllLabelBtn_clicked();
    void on_SelectImgBtn_clicked();
    void on_SaveResultBtn_clicked();
    void on_SelectSaveImgBtn_clicked();

public slots:
    void accept_QImage(QImage);

signals:
    void send_LeftImageInfo(QPoint,QString);
    void send_RightImageInfo(QPoint,QString);
    void send_LeftAndRightImageInfo(QPoint,QPoint,QString);
    void shortkey_nextImg();
    void shortkey_saveResult();
    void send_returnInfo(int);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
