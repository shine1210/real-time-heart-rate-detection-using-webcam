#include "mainthread.h"
#include "ui_mainthread.h"

mainThread::mainThread(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainThread)
{

    ui->setupUi(this);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background,Qt::black);
    setAutoFillBackground(true);
    setPalette(Pal);

    face_cascade.load("C:\\opencv3_3\\sources\\data\\haarcascades\\haarcascade_frontalface_alt2.xml");

    timer=new QTimer(this);
    timefps=new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(readframe()));
    connect(timer, SIGNAL(timeout()), this, SLOT(InterfaceUpdate()));
    connect(timefps, SIGNAL(timeout()), this, SLOT(FPS()));
    //ui->CUDAD->setNum(R_fir[50]);

}

mainThread::~mainThread()
{
    delete ui;
}

void mainThread::readframe()
{
    cap >> img;
    cvtColor(img, img, CV_BGR2RGB);
    cvtColor(img, img_gray, CV_BGR2GRAY);
    equalizeHist(img_gray, img_gray);
    face_cascade.detectMultiScale(img_gray, faces, 1.1, 10, CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, cvSize(0,0), cvSize(300,300));
    int fsize=faces.size();

    if(fsize==1||fsize==0){
        for(size_t f=0,max=faces.size();f!=max;++f){

        Point pt1(faces[f].x+faces[f].width, faces[f].y+faces[f].height);
        Point pt2(faces[f].x,faces[f].y);
        rectangle(img, pt2, pt1, cvScalar(0,255,0), 2, 8, 0);
        }
    }
    else{
        for(size_t ff=1,max=faces.size();ff!=max;++ff){
            faces.pop_back();
        }
        int fs=faces.size();
        Point pt1(faces[fs].x+faces[fs].width, faces[fs].y+faces[fs].height);
        Point pt2(faces[fs].x,faces[fs].y);
        rectangle(img, pt2, pt1, cvScalar(0,0,255), 2, 8, 0);
    }
    QImage im((unsigned char*)img.data, img.cols, img.rows, QImage::Format_RGB888);
    IM=im;




    h=im.size().height();
    w=im.size().width();
    Mat skin_HSV(h,w,CV_8UC3);

    cvtColor(img, skin_HSV, CV_BGR2HSV);
    const double skin_h=0.5, skin_hh=0.621;
    const double skin_s=0.3, skin_ss=0.55;      //HSV分割閥值範圍
    const double skin_v=0.4, skin_vv=0.579;

    double skin_hn=skin_h*180, skin_hhn=skin_hh*180;
    double skin_sn=skin_s*255, skin_ssn=skin_ss*255;      //HSV分割閥值範圍
    double skin_vn=skin_v*255, skin_vvn=skin_vv*255;

    Mat skin_new(h,w,CV_8U);
    Mat skin_rel(h,w,CV_8UC3);


    for(int i=0;i<h;++i){
        for(int j=0;j<w;++j){


            if(skin_HSV.at<Vec3b>(i,j)[0]>skin_hn && skin_HSV.at<Vec3b>(i,j)[0]<skin_hhn){
                skin_HSV.at<Vec3b>(i,j)[0]=1;
            }
            else{
                skin_HSV.at<Vec3b>(i,j)[0]=0;
            }

            if(skin_HSV.at<Vec3b>(i,j)[1]>skin_sn && skin_HSV.at<Vec3b>(i,j)[1]<skin_ssn){
                skin_HSV.at<Vec3b>(i,j)[1]=1;
            }
            else{
                skin_HSV.at<Vec3b>(i,j)[1]=0;
            }

            if(skin_HSV.at<Vec3b>(i,j)[2]>skin_vn && skin_HSV.at<Vec3b>(i,j)[2]<skin_vvn){
                skin_HSV.at<Vec3b>(i,j)[2]=1;
            }
            else{
                skin_HSV.at<Vec3b>(i,j)[2]=0;
            }

            skin_new.at<uchar>(i,j)=(skin_HSV.at<Vec3b>(i,j)[0]*skin_HSV.at<Vec3b>(i,j)[2])+(skin_HSV.at<Vec3b>(i,j)[0]*skin_HSV.at<Vec3b>(i,j)[1]);
            //skin_new.at<uchar>(i,j)=skin_HSV.at<Vec3b>(i,j)[2]*skin_HSV.at<Vec3b>(i,j)[1]*skin_HSV.at<Vec3b>(i,j)[0];

            if(skin_new.at<uchar>(i,j)>1){
                skin_new.at<uchar>(i,j)=1;

            }
            //skin_new.at<uchar>(i,j)=skin_new.at<uchar>(i,j)*255;


        }
    }

    Mat ken;

    erode(skin_new,skin_new,ken);
    dilate(skin_new,skin_new,ken);

    for(int i=0;i<h;++i){
        for(int j=0;j<w;++j){

            skin_rel.at<Vec3b>(i,j)[0]=skin_new.at<uchar>(i,j)*img.at<Vec3b>(i,j)[0];
            skin_rel.at<Vec3b>(i,j)[1]=skin_new.at<uchar>(i,j)*img.at<Vec3b>(i,j)[1];
            skin_rel.at<Vec3b>(i,j)[2]=skin_new.at<uchar>(i,j)*img.at<Vec3b>(i,j)[2];

        }
    }
//    QImage skinQ(w,h,QImage::Format_RGB888);
//    for(int i=0;i<h;++i){
//        for(int j=0;j<w;++j){
//            skinQ.setPixel(j,i,qRgb(skin_rel.at<Vec3b>(i,j)[0],skin_rel.at<Vec3b>(i,j)[1],skin_rel.at<Vec3b>(i,j)[2]));
//        }
//    }
//    skin=skinQ;

//    QImage skinQ((unsigned char*)skin_rel.data, skin_rel.cols, skin_rel.rows, QImage::Format_RGB888);
//    skin=im;

    double NUM=0,leveg=0,AVG=0;
    for(int i=faces[0].y;i<(faces[0].height+faces[0].y);++i){
            for(int j=faces[0].x;j<(faces[0].width+faces[0].x);++j){

                NUM=NUM+skin_new.at<uchar>(i,j);
                leveg=leveg+skin_rel.at<Vec3b>(i,j)[1];
                //testt.at<uchar>(i-faces[0].y,j-faces[0].x)=img.at<Vec3b>(i,j)[1];

            }
        }

    int fs=faces.size();

    if(fs>0){
        AVG=leveg/NUM;

        if(frametota<120){
            point_signal.push_back(AVG);
            frametota++;

        }
        else if(frametota==120){
            point_signal.erase(point_signal.begin());
            point_signal.push_back(AVG);

            double total=0,avg_signal=0;
            for (int i=0;i<120;++i){
                total=total+point_signal[i];
            }
            avg_signal=total/point_signal.size();
            for (int i=0;i<120;++i){
                Pures_filter[i] = point_signal[i]-avg_signal;
            }
            mainThread::conv();

        }

    }

    else{
        AVG=0;
        point_signal.clear();
        frametota=0;
        mainThread::clearPlot();

    }

    AVGP=AVG;

    if (framenum==0){
        timefps->start(1000);
    }
    ++framenum;
}

void mainThread::InterfaceUpdate()
{
    ui->fps->setNum(framesec);
    ui->Pic->setPixmap(QPixmap::fromImage(IM));
    ui->avg->setNum(AVGP);
    ui->Sec->setNum(sec);

    if(frametota==120){
        mainThread::makePlot();
    }
    ui->heart->setNum(heartbit*5.5);

}

void mainThread::FPS()
{
    timefps->stop();
    framesec=framenum;
    framenum=0;
    ++sec;
}

void mainThread::on_Start_clicked()
{
    cap.open(0);
    timer->start(15);
}

void mainThread::on_CloseCam_clicked()
{
    timer->stop();
    timefps->stop();
    cap.release();
    faces.clear();
    mainThread::clearPlot();
    framenum=0;
    frametota=0;
}

void mainThread::on_Close_clicked()
{
    close();
}

void mainThread::makePlot()
{

    QVector<double> x(120), y(120);
    for (int i=0; i<120; ++i){
      x[i] = i;
      y[i] = FPurse[i];
    }

    ui->Plot->addGraph();
    ui->Plot->graph(0)->setData(x, y);
    ui->Plot->xAxis->setLabel("x");
    ui->Plot->yAxis->setLabel("y");
    ui->Plot->xAxis->setRange(0, 125);
    ui->Plot->yAxis->setRange(3, -3);
    ui->Plot->replot();

}

void mainThread::clearPlot()
{
    QVector<double> x(120), y(120);
    ui->Plot->addGraph();
    ui->Plot->graph(0)->setData(x, y);
    ui->Plot->xAxis->setLabel("x");
    ui->Plot->yAxis->setLabel("y");
    ui->Plot->xAxis->setRange(0, 125);
    ui->Plot->yAxis->setRange(3, -3);
    ui->Plot->replot();

}


void mainThread::conv()
{
    double filter_signal[120+100];
    for (int i=0;i<120+100;++i){
        filter_signal[i]=0;
    }
    for (int i=50;i<120+50;++i){
        filter_signal[i]=Pures_filter[i-50];
    }
    double Sum=0;
    int conj=0;
    for (int i=0;i<220-50;++i){
        for (int j=i;j<(i+50);++j){
            Sum=filter_signal[j]*fir[conj]+Sum;
            ++conj;
        }
        Purse[i]=Sum;
        Sum=0;
        conj=0;
    }
    double conheart[122];
    conheart[0]=0;
    conheart[122]=0;
    for (int i=25;i<145;++i){
        FPurse[i-25]=Purse[i];
        conheart[i-(25+1)]=Purse[i];
    }
    heartbit=0;
    for (int i=0;i<120;++i){
        if (conheart[i+1]>conheart[i]&&conheart[i+1]>conheart[i+2]){
            ++heartbit;
        }
    }

}



