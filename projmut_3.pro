#-------------------------------------------------
#
# Project created by QtCreator 2017-12-24T12:24:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = projmut_3
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=C:\QT_Project\QT_OpenCV3_2\include\opencv
INCLUDEPATH +=C:\QT_Project\QT_OpenCV3_2\include\opencv2
INCLUDEPATH +=C:\QT_Project\QT_OpenCV3_2\include


LIBS +=C:\QT_Project\QT_OpenCV3_2\lib\libopencv_calib3d320.dll.a\
     C:\QT_Project\QT_OpenCV3_2\lib\libopencv_core320.dll.a\
     C:\QT_Project\QT_OpenCV3_2\lib\libopencv_features2d320.dll.a\
     C:\QT_Project\QT_OpenCV3_2\lib\libopencv_flann320.dll.a\
     C:\QT_Project\QT_OpenCV3_2\lib\libopencv_highgui320.dll.a\
     C:\QT_Project\QT_OpenCV3_2\lib\libopencv_imgcodecs320.dll.a\
     C:\QT_Project\QT_OpenCV3_2\lib\libopencv_imgproc320.dll.a\
     C:\QT_Project\QT_OpenCV3_2\lib\libopencv_ml320.dll.a\
     C:\QT_Project\QT_OpenCV3_2\lib\libopencv_objdetect320.dll.a\
     C:\QT_Project\QT_OpenCV3_2\lib\libopencv_photo320.dll.a\
     C:\QT_Project\QT_OpenCV3_2\lib\libopencv_shape320.dll.a\
     C:\QT_Project\QT_OpenCV3_2\lib\libopencv_stitching320.dll.a\
     C:\QT_Project\QT_OpenCV3_2\lib\libopencv_superres320.dll.a\
     C:\QT_Project\QT_OpenCV3_2\lib\libopencv_video320.dll.a\
     C:\QT_Project\QT_OpenCV3_2\lib\libopencv_videoio320.dll.a\
     C:\QT_Project\QT_OpenCV3_2\lib\libopencv_videostab320.dll.a\



SOURCES += main.cpp \
           mainthread.cpp \
    qcustomplot.cpp

HEADERS += mainthread.h \
    qcustomplot.h

FORMS += mainthread.ui

QMAKE_CXXFLAGS += -std=gnu++11
