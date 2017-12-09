#ifndef IMGPROCTHREAD_H
#define IMGPROCTHREAD_H

#include <QObject>
#include <QThread>
#include <QPoint>
#include <opencv.hpp>
#include <QImage>
using namespace cv;
class ImgProcThread : public QThread
{
    Q_OBJECT
public:
    ImgProcThread();
public:
    Mat OriImage;
    Mat dispImage;
    QPoint LeftPoint;
    QPoint RightPoint;
    bool isdrawleft;
    bool isdrawright;
    bool isdrawAll;
public:
    QImage convertMatToQImage(Mat &mat);
    Mat   convertQImageToMat(QImage &image);
signals:
    void send_drawImage(QImage);
public slots:
    void accept_leftargImage(QPoint,QString);
    void accept_rightargImage(QPoint,QString);
    void accept_leftAndRightImage(QPoint,QPoint,QString);
protected:
    void run();
};

#endif // IMGPROCTHREAD_H
