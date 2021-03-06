

#include <QApplication>
#include <QLibraryInfo>

#include "MainWindow.h"
#include "Task.h"

#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {
    new QApplication(argc,argv);

    cout<<"Installer version: "<<VERSION<<endl;

    if(!Task::task.loadConfigFile(argv[1], QString(argv[2]).toLong())){
        return 1;
    }

    MainWindow w;
    w.show();

    return QApplication::exec();
}
