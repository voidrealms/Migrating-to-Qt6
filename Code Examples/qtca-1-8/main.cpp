#include <QCoreApplication>
#include <QDebug>
#include <QThreadPool>
#include <QSemaphore>
#include "worker.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QStringList data;
    for(int i = 0; i < 100; i++)
    {
        data.append(QString::number(i));
    }

    QThreadPool* pool = QThreadPool::globalInstance();
    QSemaphore sema(100);

    for (int i = 0;i < data.length();i++)
    {
        Worker* worker = new Worker(&a,&data, &sema, i);
        worker->setAutoDelete(true);
        pool->start(worker);
    }
    for (int i = 0;i < data.length();i++)
    {
        Worker* worker = new Worker(&a,&data, &sema, i);
        worker->setAutoDelete(true);
        pool->start(worker);
    }
    pool->waitForDone();

    foreach(QString string, data)
    {
        qInfo() << string;
    }

    return a.exec();
}
