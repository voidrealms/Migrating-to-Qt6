#include "watcher.h"

watcher::watcher(QObject *parent) : QObject(parent)
{

}

void watcher::messageChanged(QString message)
{
    qInfo() << message;
}
