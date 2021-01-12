#include <QCoreApplication>
#include <QDebug>
#include "logger.h"
#include "test.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qInfo() << "File: " << logger::filename;
    logger::attach();

    qInfo() << "test!";

    logger::logging = false;
    qInfo() << "Don't log this!";
    logger::logging = true;

    test t;
    t.testing();

    qInfo() << "Finished!";
    return a.exec();
}
