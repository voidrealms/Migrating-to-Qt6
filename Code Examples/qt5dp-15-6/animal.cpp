#include "animal.h"

Animal::Animal(QObject *parent) : QObject(parent)
{
    clear();

    //For concurrent IO
    connect(&m_watcher,&QFutureWatcher<bool>::finished,this,&Animal::concurrentFinished);

}

bool Animal::fromIO(QIODevice *device)
{
    qInfo() << "fromIO";
    if(!device->isReadable())
    {
        emit error(QString("Device is not readable!"));
        return false;
    }

    QDataStream stream(device);
    stream.setVersion(QDataStream::Qt_5_10);
    stream >> m_name;
    stream >> m_species;
    stream >> m_age;
    stream >> m_fed;

    return true;
}

bool Animal::toIO(QIODevice *device)
{
    qInfo() << "toIO";
    if(!device->isWritable())
    {
        emit error(QString("Device is not writeable!"));
        return false;
    }

    QDataStream stream(device);
    stream.setVersion(QDataStream::Qt_5_10);
    stream << m_name;
    stream << m_species;
    stream << m_age;
    stream << m_fed;

    return true;
}

void Animal::waitForFinished()
{
    //waiting sucks, this is for command line stuff
     m_future.waitForFinished();
}

QString Animal::name() const
{
    return m_name;
}

void Animal::setName(const QString &name)
{
    m_name = name;
    emit nameChanged();
}

QString Animal::species() const
{
    return m_species;
}

void Animal::setSpecies(const QString &species)
{
    m_species = species;
    emit speciesChanged();
}

int Animal::age() const
{
    return m_age;
}

void Animal::setAge(int age)
{
    m_age = age;
    emit ageChanged();
}

QDateTime Animal::fed() const
{
    return m_fed;
}

void Animal::setFed(const QDateTime &fed)
{
    m_fed = fed;
    emit fedChanged();
}

void Animal::fromFile(QString path)
{
    //Move the IO to a new thread and let Qt  take care of the details
    //m_watcher.setFuture(m_future);
    //m_future = QtConcurrent::run(this,&Animal::concurrentIO,path, QIODevice::ReadOnly);
    m_future = QtConcurrent::run(&Animal::concurrentIO,this,path, QIODevice::ReadOnly);
    m_watcher.setFuture(m_future);
}

void Animal::toFile(QString path)
{
    //Move the IO to a new thread and let Qt  take care of the details
    // m_future = QtConcurrent::run(this,&Animal::concurrentIO,path, QIODevice::WriteOnly);
    m_future = QtConcurrent::run(&Animal::concurrentIO,this,path, QIODevice::WriteOnly);
    m_watcher.setFuture(m_future);
}

void Animal::clear()
{
    m_age = 0;
    m_name = "Unnamed";
    m_species = "Unknown";
    m_fed = QDateTime::currentDateTime();
}

void Animal::concurrentFinished()
{
    qInfo() << "concurrentFinished";
    if(m_future.results().first() == true)
    {
        emit finished();
    }
    else
    {
        emit error("Something went wrong...");
    }
}

bool Animal::concurrentIO(QString path, QIODevice::OpenModeFlag flag)
{
    qInfo() << "concurrentIO started";
    qInfo() << QThread::currentThread();
    QFile file(path);
    if(!file.open(flag))
    {
        emit error(file.errorString());
        return false;
    }

    bool ok = false;
    switch (flag)
    {
    case QIODevice::WriteOnly: //save
        ok = toIO(&file);
        break;
    case QIODevice::ReadOnly: //load
        ok = fromIO(&file);
        break;
    default:
        ok = false;
        break;
    }
    file.close();

    qInfo() << "concurrentIO finished";

    return ok;
}
