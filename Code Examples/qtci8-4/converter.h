#ifndef CONVERTER_H
#define CONVERTER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QVariant>
#include <QVariantMap>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMap>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "test.h"

class converter : public QObject
{
    Q_OBJECT
public:
    explicit converter(QObject *parent = nullptr);

    static void writeJson(test *obj, QString path);
    static test* readJson(QString path);

    static void writeXml(test *obj, QString path);
    static test* readXml(QString path);


signals:

public slots:
};

#endif // CONVERTER_H
