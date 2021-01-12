#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <QObject>
#include <QDebug>
#include <QTextStream>
#include <QtConcurrent>
#include <QThread>

class CommandLine : public QObject
{
    Q_OBJECT
public:
    explicit CommandLine(QObject *parent = nullptr, FILE *fileHandle = nullptr);

    [[noreturn]] void monitor();

signals:
    void command(QString value);

public slots:

private:
    QTextStream cin;

};

#endif // COMMANDLINE_H
