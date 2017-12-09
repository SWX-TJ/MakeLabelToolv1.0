#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isLeftPoint = false;
    isRightPoint = false;
    isLeftPointFinish = false;
    isRightPointFinish = false;
    isfirstSelect = true;
    traing_TempleteImageNum= 0;
    testing_TempleteImageNum =0;
    neededLabelImgIndex = 1;
    m_makeimg = new ImgProcThread;
    m_player = new MusicPlayer(this);
    ui->MusicLayout->addWidget(m_player);
    connect(this,SIGNAL(send_LeftImageInfo(QPoint,QString)),m_makeimg,SLOT(accept_leftargImage(QPoint,QString)));
    connect(this,SIGNAL(send_RightImageInfo(QPoint,QString)),m_makeimg,SLOT(accept_rightargImage(QPoint,QString)));
    connect(this,SIGNAL(send_LeftAndRightImageInfo(QPoint,QPoint,QString)),m_makeimg,SLOT(accept_leftAndRightImage(QPoint,QPoint,QString)));
    connect(this,SIGNAL(shortkey_nextImg()),this,SLOT(on_SelectImgBtn_clicked()));
    connect(this,SIGNAL(shortkey_saveResult()),this,SLOT(on_SaveResultBtn_clicked()));
    connect(m_makeimg,SIGNAL(send_drawImage(QImage)),this,SLOT(accept_QImage(QImage)));
    m_makeimg->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_S:
        shortkey_nextImg();
        break;
    case Qt::Key_J:
        shortkey_saveResult();
        break;
    case Qt::Key_Escape:
        exit(EXIT_SUCCESS);
        break;
    }
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(Qt::LeftButton == event->button())
    {
        isLeftPoint = true;
        isLeftPointFinish = false;
    }
    if(Qt::RightButton == event->button())
    {
        isRightPoint = true;
        isRightPointFinish = false;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(isLeftPoint)
    {
        leftPoint.setX(event->x());
        leftPoint.setY(event->y());
        QString temp_leftPoint_x,temp_leftPoint_y;
        ui->right_aix_x->setText(temp_leftPoint_x.setNum(leftPoint.x()));
        ui->right_aix_y->setText(temp_leftPoint_y.setNum(leftPoint.y()-40));
        if(isRightPointFinish)
        {
            send_LeftAndRightImageInfo(leftPoint,rightFnishPoint,File_path);
        }
        else
        {
            send_LeftImageInfo(leftPoint, File_path);
        }
    }
    if(isRightPoint)
    {
        rightPoint.setX(event->x());
        rightPoint.setY(event->y());
        QString temp_rightPoint_x,temp_rightPoint_y;
        ui->left_aix_x->setText(temp_rightPoint_x.setNum(rightPoint.x()));
        ui->left_aix_y->setText(temp_rightPoint_y.setNum(rightPoint.y()-40));
        if(isLeftPointFinish)
        {
            send_LeftAndRightImageInfo(leftFnishPoint,rightPoint,File_path);
        }
        else
        {
            send_RightImageInfo(rightPoint, File_path);
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(Qt::LeftButton == event->button())
    {
        isLeftPoint = false;
        isLeftPointFinish = true;
        leftFnishPoint.setX(event->x());
        leftFnishPoint.setY(event->y());
    }
    if(Qt::RightButton == event->button())
    {
        isRightPoint = false;
        isRightPointFinish = true;
        rightFnishPoint.setX(event->x());
        rightFnishPoint.setY(event->y());
    }
}

QImage MainWindow::convertMatToQImage(Mat &mat)
{
    QImage img;
    int nChannel=mat.channels();
    if(nChannel==3)
    {
        cvtColor(mat,mat,CV_BGR2RGB);
        img = QImage((const unsigned char*)mat.data,mat.cols,mat.rows,QImage::Format_RGB888);
    }
    if(nChannel==4)
    {
        img = QImage((const unsigned char*)mat.data,mat.cols,mat.rows,QImage::Format_ARGB32);
    }
    if(nChannel==1)
    {
        img = QImage((const unsigned char*)mat.data,mat.cols,mat.rows,QImage::Format_Indexed8);
    }
    return img;
}

Mat MainWindow::convertQImageToMat(QImage &image)
{
    cv::Mat mat;
    switch (image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    default:
        break;
    }
    return mat;
}

bool MainWindow::isDirexits(QString filedir)
{
    QDir dir(filedir);
    if(dir.exists())
    {
        return true;
    }
    else
    {
        bool ok = dir.mkpath(filedir);
        if(ui->LabelPhase->currentText()=="Training")
        {
            traing_TempleteImageNum = 0;
        }
        else if(ui->LabelPhase->currentText()=="Testing")
        {
            testing_TempleteImageNum =0;
        }
        return ok;
    }
}

void MainWindow::on_ExitBtn_clicked()
{
    m_makeimg->quit();
    exit(EXIT_SUCCESS);
}

void MainWindow::on_InsertNewLabelBtn_clicked()
{
    QString newLabel = ui->NewLabelEdit->text();
    if( ui->LabelBox->findText(newLabel)==-1)
    {
        ui->LabelBox->insertItem(ui->LabelBox->count(),newLabel);
    }
    else
    {
        QMessageBox::information(this,"提示","已经有相同的标签存在！");
    }
}

void MainWindow::on_deteCurrentLabelBtn_clicked()
{
    ui->LabelBox->removeItem(ui->LabelBox->currentIndex());
}

void MainWindow::on_DeleteAllLabelBtn_clicked()
{

}

void MainWindow::on_SelectImgBtn_clicked()
{

    if(neededLabelImgIndex==neededLabelImageNum-2)
    {
        ui->SelectImgBtn->setText(QString("标记完成"));
    }
    else
    {
        if(isfirstSelect)
        {
            isfirstSelect = false;
            ui->SelectImgBtn->setText(QString("下一张"));
            neededLabelImageFilePath = QFileDialog::getExistingDirectory();
            QDir *dir = new QDir(neededLabelImageFilePath);
            QStringList filter;
            neededLabelImageFileInfo = new QList<QFileInfo>(dir->entryInfoList(filter));
            neededLabelImageNum = neededLabelImageFileInfo->count();
            QString filepath = neededLabelImageFilePath.replace('/',"\\");
            File_path = filepath+QString("\\1 (%1).bmp").arg(neededLabelImgIndex);
            std::string stdmatchfilename = File_path.toStdString();
            OriImage = imread(stdmatchfilename);
            DispImage =  convertMatToQImage(OriImage);
            ui->ImageDisp->setPixmap(QPixmap::fromImage(DispImage));
            neededLabelImgIndex++;
            ui->ImgNumCount->setNum(neededLabelImgIndex-1);
        }
        else
        {
            ui->SelectImgBtn->setText(QString("下一张"));
            QString filepath = neededLabelImageFilePath.replace('/',"\\");
            File_path = filepath+QString("\\1 (%1).bmp").arg(neededLabelImgIndex);
            std::string stdmatchfilename = File_path.toStdString();
            OriImage = imread(stdmatchfilename);
            DispImage =  convertMatToQImage(OriImage);
            ui->ImageDisp->setPixmap(QPixmap::fromImage(DispImage));

            neededLabelImgIndex++;
            ui->ImgNumCount->setNum(neededLabelImgIndex-1);
        }
    }
}

void MainWindow::accept_QImage(QImage oriImage)
{
    ui->ImageDisp->setPixmap(QPixmap::fromImage(oriImage));
}

void MainWindow::on_SaveResultBtn_clicked()
{
    cv::Point stdleftPoint,stdrightPoint;
    if(rightFnishPoint.x()==0)
    {
        OriImage.copyTo(TempleteImage);
        isbinaryClassfiy = true;
    }
    else
    {
        isbinaryClassfiy = false;
        stdleftPoint.x =  rightFnishPoint.x();
        stdleftPoint.y =  rightFnishPoint.y()-40;
        stdrightPoint.x = leftFnishPoint.x();
        stdrightPoint.y = leftFnishPoint.y()-40;
        OriImage(Rect(stdleftPoint.x,stdleftPoint.y,(stdrightPoint.x-stdleftPoint.x),(stdrightPoint.y-stdleftPoint.y))).copyTo(TempleteImage);
    }
    if(ui->LabelPhase->currentText()=="Training")
    {
        QString tempfilePath = selectSaveImgDir.replace("/","\\")+QString("\\training");
        ui->FilePathEdit->setText(tempfilePath);
        QString secondfilepath = ui->LabelBox->currentText();
        QString fullfilepath = tempfilePath+QString("\\")+secondfilepath;
        isDirexits(fullfilepath);
        QString saveimageListFilename = fullfilepath+QString("\\trainImageList.txt");
        if(trainingFileList.fileName()!=saveimageListFilename)
        {

         trainingFileList.close();
         trainingFileList.setFileName(saveimageListFilename);
        if(!trainingFileList.open(QFile::WriteOnly|QFile::Append|QIODevice::Text))
        {

        }
        }

        QTextStream trainingfileout(&trainingFileList);
        for(size_t i=0;i<TrainingLabelIndex.size();i++)
        {
            if(TrainingLabelIndex.at(i)==ui->LabelBox->currentText())
            {
                traing_TempleteImageNum = TrainingLabelIndexLastnum.at(i);
                break;
            }
        }
        QString tempfileName = secondfilepath+QString("(%1).bmp").arg(traing_TempleteImageNum);
        std::string savetempfile = (fullfilepath+QString("\\")+tempfileName).toStdString();
        Mat grayTempleteImage;
        cvtColor(TempleteImage,grayTempleteImage,COLOR_BGR2GRAY);
        imwrite(savetempfile,grayTempleteImage);
     if(isbinaryClassfiy)
     {
         trainingfileout<<tempfileName<<"  "<<ui->LabelBox->currentText()<<endl;
     }
     else
     {
        trainingfileout<<tempfileName<<"  "<<stdleftPoint.x<<","<<stdleftPoint.y<<"  "<<stdrightPoint.x<<","<<stdrightPoint.y<<"  "<<ui->LabelBox->currentText()<<endl;
     }
        traing_TempleteImageNum++;
        for(size_t i=0;i<TrainingLabelIndex.size();i++)
        {
            if(TrainingLabelIndex.at(i)==ui->LabelBox->currentText())
            {
                TrainingLabelIndexLastnum.replace(i,traing_TempleteImageNum);
                break;
            }
        }
        TrainingLabelIndex.append(ui->LabelBox->currentText());
        TrainingLabelIndexLastnum.append(traing_TempleteImageNum);
    }
    else if(ui->LabelPhase->currentText()=="Testing")
    {
        QString tempfilePath = selectSaveImgDir.replace("/","\\")+QString("\\testing");
        ui->FilePathEdit->setText(tempfilePath);
        QString secondfilepath = ui->LabelBox->currentText();
        QString fullfilepath = tempfilePath+QString("\\")+secondfilepath;
        isDirexits(fullfilepath);
        QString saveimageListFilename = fullfilepath+QString("\\testImageList.txt");
        testingFileList.setFileName(saveimageListFilename);
        if(!testingFileList.open(QFile::WriteOnly|QFile::Append))
        {

        }
        QTextStream testingfileout(&testingFileList);
        for(size_t i=0;i<TestingLabelIndex.size();i++)
        {
            if(TestingLabelIndex.at(i)==ui->LabelBox->currentText())
            {
                testing_TempleteImageNum = TestingLabelIndexLastnum.at(i);
                break;
            }
        }
        QString tempfileName = secondfilepath+QString("(%1).bmp").arg(testing_TempleteImageNum);
        std::string savetempfile = (fullfilepath+QString("\\")+tempfileName).toStdString();
        Mat grayTempleteImage;
        cvtColor(TempleteImage,grayTempleteImage,COLOR_BGR2GRAY);
        imwrite(savetempfile,grayTempleteImage);
        testingfileout<<tempfileName<<"  "<<stdleftPoint.x<<","<<stdleftPoint.y<<"  "<<stdrightPoint.x<<","<<stdrightPoint.y<<"  "<<ui->LabelBox->currentText()<<endl;
        testing_TempleteImageNum++;
        for(size_t i=0;i<TestingLabelIndex.size();i++)
        {
            if(TestingLabelIndex.at(i)==ui->LabelBox->currentText())
            {
                TestingLabelIndexLastnum.replace(i,testing_TempleteImageNum);
                break;
            }
        }
        TestingLabelIndex.append(ui->LabelBox->currentText());
        TestingLabelIndexLastnum.append(testing_TempleteImageNum);
    }
}

void MainWindow::on_SelectSaveImgBtn_clicked()
{
    selectSaveImgDir = QFileDialog::getExistingDirectory(this,QString("选择样本保存目录"),"/");
    ui->FilePathEdit->setText(selectSaveImgDir);

}
