#include <QGuiApplication>
#include <QQmlApplicationEngine>

/*
 What
 using the class in a qml app

 Description
 Testing our class in a qml app

 Why
 QML runs on just about anything.
 The storage on your desktop is vastly different than on a raspberri pi or a android phone

 Example
 Widgets app
 QT += concurrent

 Note
 QML Date times suck

 */

#include "animal.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<Animal>("com.company.animal",1,0,"Animal");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
