#include "worker.h"

Worker::Worker(QObject *parent, QStringList *data, QSemaphore *sema, int position) : QObject(parent)
{
    this->sema = sema;
    this->data = data;
    this->position = position;
}


void Worker::run()
{
    if(!data || !sema)
    {
        qInfo() << "Missing pointers!";
        return;
    }

    QString t;
    //t.sprintf("%08p", QThread::currentThread());
    //t.asprintf("%8p", QThread::currentThread());
    sema->acquire(1);
    data->replace(position,QString::number(position) + " - " + QThread::currentThread()->objectName());
    sema->release();

    qInfo() << t << " Finished " << position;

}
