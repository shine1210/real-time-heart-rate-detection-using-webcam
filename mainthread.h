#ifndef MAINTHREAD_H
#define MAINTHREAD_H

#include <QWidget>
#include <opencv2/opencv.hpp>
#include <vector>
#include <stdio.h>
#include <iostream>
#include "qcustomplot.h"
#include <QVector>




#include <QImage>
#include <QTimer>
#include <QDebug>


using namespace cv;
using namespace std;


namespace Ui {
class mainThread;
}

class mainThread : public QWidget
{
    Q_OBJECT

public:
    explicit mainThread(QWidget *parent = 0);
    ~mainThread();

public slots:
    void readframe();
    void InterfaceUpdate();
    void FPS();

private slots:
    void on_Start_clicked();
    void on_CloseCam_clicked();
    void on_Close_clicked();
    void makePlot();
    void clearPlot();
    void conv();


private:
    Ui::mainThread *ui;
    VideoCapture cap;
    Mat img, img_gray;
    CascadeClassifier face_cascade;
    vector<Rect> faces;
    QImage IM, skin;
    QTimer *timer, *timefps;
    int framenum=0, framesec=0, h, w, frametota=0, sec=0, heartbit=0;
    //fir[0-50]
    double fir[51]={0.000881047339103894,-0.000402426144095514,-0.000495952240242322,0.000616489479659442,0.000752888093287427,-0.00231071435674249,-0.00666311584683587,-0.00670747081224631,-0.000852795595774669,0.00372211615562370,-4.13066488570329e-18,-0.00560936471473143,0.00194192782285260,0.0231928862143821,0.0352115030265722,0.0187813912314622,-0.00944281464790146,-0.0118728663288417,0.0143752948260676,0.0168487638418682,-0.0502278379625430,-0.145836294203238,-0.157808656316407,-0.0243391019915792,0.172422791337616,0.266340517254483,0.172422791337616,-0.0243391019915792,-0.157808656316407,-0.145836294203238,-0.0502278379625430,0.0168487638418682,0.0143752948260676,-0.0118728663288417,-0.00944281464790146,0.0187813912314622,0.0352115030265722,0.0231928862143821,0.00194192782285260,-0.00560936471473143,-4.13066488570329e-18,0.00372211615562370,-0.000852795595774669,-0.00670747081224631,-0.00666311584683587,-0.00231071435674249,0.000752888093287427,0.000616489479659442,-0.000495952240242322,-0.000402426144095514,0.000881047339103894};
    double Pures_filter[120],Purse[170],FPurse[120];
    vector<double> point_signal;
    double AVGP=0;

};

#endif // MAINTHREAD_H
