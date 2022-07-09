//
// Created by maicss on 22-7-3.
//
#include <QApplication>

#include "MainWindow.h"
#include "TarFile.h"
#include <iostream>

using namespace std;
int main(int argc, char **argv){
//    QApplication a(argc,argv);
//    MainWindow w;
//    w.show();
//
//    return a.exec();
    TarFile file;
    file.open("/home/maicss/下载/wzzd2.tar",0);
    cout<<file.getNodeCount();
//    cout<<file.getNodeCount();
    file.unpack(HomeDir()+"/test","");
//    cout<<file.readTextFile("7daystodie.desktop").toStdString();
}