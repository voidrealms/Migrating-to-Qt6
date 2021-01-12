#include <QCoreApplication>
#include <QIODevice>
#include <QDir>
#include <QFile>
#include <QString>
#include <QByteArray>
#include <QDebug>
#include <QTextStream>

bool write(QString path, QByteArray data) {
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly)) {
        qWarning() << file.errorString();
        return false;
    }

    qint64 bytes = file.write(data);
    file.close();
    if(bytes) return true;

    return false;
}

bool createfile(QString path) {
    QByteArray data;
    for(int i = 0; i < 5; i++) {
        //data.append(QString::number(i));
        data.append(QString::number(i).toUtf8());
        data.append(" Hello World\r\n");
    }

    return write(path,data);
}

void readFile(QString path) {
    QFile file(path);
    if(!file.exists()) {
        qWarning() << "File not found";
        return;
    }

    if(!file.open(QIODevice::ReadOnly)) {
        qWarning() << file.errorString();
        return;
    }

    qInfo() << "**** Reading File";
    qInfo() << file.readAll(); //Best small files!
    qInfo() << "**** Done";

    file.close();
}

void readLines(QString path) {
    QFile file(path);
    if(!file.exists()) {
        qWarning() << "File not found";
        return;
    }

    if(!file.open(QIODevice::ReadOnly)) {
        qWarning() << file.errorString();
        return;
    }

    qInfo() << "**** Reading File";
    while (!file.atEnd()) {
        QString line(file.readLine());
        qInfo() << "Read:" << line.trimmed(); //best with text files!
    }
    qInfo() << "**** Done";

    file.close();
}

void readBytes(QString path) {
    QFile file(path);
    if(!file.exists()) {
        qWarning() << "File not found";
        return;
    }

    if(!file.open(QIODevice::ReadOnly)) {
        qWarning() << file.errorString();
        return;
    }

    qInfo() << "**** Reading File";
    while (!file.atEnd()) {
        qInfo() << "Read: " << file.read(5); // best with larger file or structs
    }
    qInfo() << "**** Done";

    file.close();
}




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString path = QDir::currentPath() + QDir::separator() + "test.txt";
    qInfo() << "Path: " << path;

    if(createfile(path)) {
        readFile(path);
        readLines(path);
        readBytes(path);
    }

    return a.exec();
}
