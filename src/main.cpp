#include <iostream>

#include <QApplication>
#include "MainWindow.h"
#include "Task.h"
#include "utils.h"
using namespace std;
int main(int argc, char *argv[]) {
    new QApplication(argc,argv);
    if(!Task::task.loadConfigFile(argv[1])){
        return 1;
    }

    MainWindow w;
    w.show();

//
//    TarFile tarFile(argv[1]);
//    if (tarFile.IsValidTarFile()) {
//        cout<<"IsValid"<<endl;
//    } else {
//        cout<<"NotValid"<<endl;
//    }
//    tarFile.unzipToDir("/home/maicss/test");

    return QApplication::exec();
}
