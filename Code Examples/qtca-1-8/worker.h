#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QRunnable>
#include <QSemaphore>

class Worker : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr, QStringList* data = nullptr, QSemaphore* sema = nullptr, int position = -1);
    void run();
signals:

public slots:

private:
    QStringList* data;
    QSemaphore* sema;
    int position;
};

#endif // WORKER_H
