/*
 * Copyright (C) 2020, KylinSoft Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Authors: baijincheng <baijincheng@kylinos.cn>
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define KYLINRECORDER "org.kylin-recorder-data.settings"
#define FITTHEMEWINDOW "org.ukui.style"
#include <QGSettings>

#include <QWidget>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QProgressBar>
#include <QPainter>
#include <QStyle>
#include <QToolButton>
#include <QLabel>
#include <QSlider>
#include <QThread>


#include <QTimer>
#include <QTime>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QDesktopWidget>
#include <QtMultimedia>//使用多媒体时要引用这个并且在pro中加QT += multimedia multimediawidgets
#include <QAudioRecorder>
#include <QListWidget>

#include <QFile>
#include <QStackedLayout>//此类提供了多页面切换的布局，一次只能看到一个界面
#include <QMouseEvent>

#include <QPainter>
#include <QSettings>
#include "mywave.h"
#include "mythread.h"
#include "settings.h"
#include "save.h"
#include "itemswindow.h"
#include "miniwindow.h"

#include <unistd.h>
#include <fcntl.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public://放在public都是有原因的因为不同类之间中调用需要公用！！
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QMessageBox *WrrMsg;
    QGSettings  *defaultPathData= nullptr;
    QGSettings *themeData=nullptr;//主题的setting
    QString theme = "ukui-default";
    bool isMax = false;
    QTime cut;
    int valueArray[110];

    Settings set;
    Save saveas;

    //QString fileName;
    QString daultfileName;

    int ad = 1;
    int tag=0;//是否检测到输入设备

    int once=0;//没执行过

    QThread *thread;//主线程
    MyThread *myThread;//子线程
    MiniWindow mini;
    static MainWindow *mutual;//！！！指针类型静态成员变量
    bool strat_pause=false;//开始和暂停1
    QStackedLayout *m_pStackedLayout;//堆叠布局

    QLabel *lb;
    QLabel *piclb;//窗体左上角图片Label
    ItemsWindow *itemswindow;

    QListWidget *list;
    QListWidgetItem *aItem;//列表的Item

    QLabel *fileListlb;//文件列表
    QFile *file;
    void initThemeGsetting();
    void initFunctionGsetting();
    void themeButton(QString themeColor);
    void themeStyle(QString themeColor);
    void themeWindow(QString themeColor);

    void MainWindowLayout();

    QString playerTotalTime(QString filePath);
    int itemSelect=0;


    int pre=0;
    int now=0;
    QTimer *pTimer;//1
    QTime baseTime;//1
private:


    QList<int> maxNum;//存储振幅的大小的整型列表
    bool stop=false;//停止

    bool max_min=false;//最大最小化

    QAudioRecorder *audioRecorder;
    QLabel *seatlb;

    QToolButton *setButton;
    QToolButton *miniButton;//mini模式切换按钮
    QToolButton *minButton;//最小化按钮
    QToolButton *maxButton;//最大化按钮
    QToolButton *closeButton;

    QToolButton *recordButton;


    QToolButton *stopButton;
    QToolButton *play_pauseButton;




    QWidget *mainWid;

    QWidget *leftMainWid;//主左Wid
    QWidget *rightMainWid;//主右Wid
    QWidget *titleLeftWid;//左标题栏Wid
    QWidget *titleRightWid;//右标题栏Wid

    //QWidget *titleWid;替换的
    QWidget *recordButtonWid;//录制按钮Wid

    QWidget *listWid;//文件列表Wid


    QHBoxLayout *titleLeftLayout;//左标题栏布局
    QHBoxLayout *titleRightLayout;//右标题栏布局

    QVBoxLayout *listLayout;//文件列表布局
    //QHBoxLayout *titleLayout;//替换

    QHBoxLayout *btnLayout;
    QVBoxLayout *leftMainWidLayout;//主Wid的左布局
    QVBoxLayout *rightMainWidLayout;//主Wid的右布局
    QHBoxLayout *mainLayout;


    QHBoxLayout *layout1;
    QHBoxLayout *layout2;
    QHBoxLayout *layout3;
    QHBoxLayout *layout4;
    QVBoxLayout *ui_2Layout;

    QWidget *ui_2Wid;//第二个页面
    QWidget *timeWid;
    QWidget *waveWid;//波形图的容器
    QWidget *voiceWid;
    QWidget *playWid;

    QLabel *showTimelb;
    QFrame *fm;
    QLabel *voicelb;


    //显示的时间
    QString timeStr;


    QString firstGetrecordList="";

    bool isPress;
    QPoint winPos;
    QPoint dragPos;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void checkSingle();//检查单例模式


signals://主线程的信号
    void startThread();
    void closeSignal();

    void startRecord();
    void stopRecord();
    void playRecord();
    void pauseRecord();
    void pageChange();


private://音频相关

    QSlider *slider;

    QVector<myWave*> mywave;




public slots:
    void recordPaint(int); 
    void mainWindow_page2();
    void switchPage();
    void play_pause_clicked();
    void stop_clicked();
    void updateDisplay();
    void changeVoicePicture();

    void goset();//弹出设置窗体

    void miniShow();
    void minShow();
    void maxShow();

    void slotOnItemDoubleClicked(QListWidgetItem *item);
    void slotItemEntered(QListWidgetItem *item);

    void handlingSlot(QString str);
    void slotListItemAdd(QString fileName,int i);
};

#endif // MAINWINDOW_H
