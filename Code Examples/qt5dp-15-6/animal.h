#ifndef ANIMAL_H
#define ANIMAL_H

#include <QObject>
#include <QDebug>
#include <QIODevice>
#include <QDateTime>
#include <QFile>
#include <QDataStream>
#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QThread>

class Animal : public QObject
{
    Q_OBJECT

    //Q_PROPERTY is needed for QML!!!
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString species READ species WRITE setSpecies NOTIFY speciesChanged)
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)
    Q_PROPERTY(QDateTime fed READ fed WRITE setFed NOTIFY fedChanged)

public:
    explicit Animal(QObject *parent = nullptr);

public:
    bool fromIO(QIODevice *device); //ANY IODevice....files, buffers, sockets
    bool toIO(QIODevice *device); //ANY IODevice....files, buffers, sockets
    void waitForFinished(); //Mainly for command line testing

    QString name() const;
    void setName(const QString &name);

    QString species() const;
    void setSpecies(const QString &species);

    int age() const;
    void setAge(int age);

    QDateTime fed() const;
    void setFed(const QDateTime &fed);

public slots:
    void fromFile(QString path);
    void toFile(QString path);
    void clear();

private slots:
    void concurrentFinished();

signals:
    void nameChanged();
    void speciesChanged();
    void ageChanged();
    void fedChanged();
    void error(QString message);
    void finished();

private:
    QString m_name;
    QString m_species;
    int m_age;
    QDateTime m_fed;
    QFutureWatcher<bool> m_watcher;
    QFuture<bool> m_future;

    bool concurrentIO(QString path, QIODevice::OpenModeFlag flag);

};

#endif // ANIMAL_H
