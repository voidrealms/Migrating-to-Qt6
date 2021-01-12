#ifndef SPECIALVALIDATOR_H
#define SPECIALVALIDATOR_H

#include <QObject>
#include <QDebug>
//#include <QRegExp>
#include <QRegularExpression>
#include "../interfaces/iValidator.h"

class SpecialValidator : public QObject, public iValidator
{
    Q_OBJECT
public:
    explicit SpecialValidator(QObject *parent = nullptr);

signals:


    // iValidator interface
public:
    bool check(QString &value) override;
    bool checkNext(QString &value) override;
};

#endif // SPECIALVALIDATOR_H
