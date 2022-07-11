//
// Created by maicss on 22-7-3.
//
#include <QApplication>
#include "MainWindow.h"
using namespace std;
int main(int argc, char **argv){
    QApplication a(argc,argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}