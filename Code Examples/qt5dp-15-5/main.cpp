#include "dialog.h"

/*
 What
 using the class in a widgets app

 Description
 Testing our class in a widgets app

 Why
 Imaging saving to a slow network drive or a thumb drive

 Example
 Widgets app
 QT += concurrent

 */

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    return a.exec();
}
