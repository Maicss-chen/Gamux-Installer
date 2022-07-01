

#include <QApplication>

#include "MainWindow.h"
#include "Task.h"

#include <iostream>
using namespace std;
int main(int argc, char *argv[]) {
    new QApplication(argc,argv);
    if(!Task::task.loadConfigFile(argv[1])){
        return 1;
    }

    MainWindow w;
    w.show();

    return QApplication::exec();
}
