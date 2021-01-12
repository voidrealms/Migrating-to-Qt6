#ifndef NUMBERVALIDATOR_H
#define NUMBERVALIDATOR_H

#include <QObject>
#include <QDebug>
//#include <QRegExp>
#include <QRegularExpression>
#include "../interfaces/iValidator.h"

class NumberValidator : public QObject, public iValidator
{
    Q_OBJECT
public:
    explicit NumberValidator(QObject *parent = nullptr);

signals:


    // iValidator interface
public:
    bool check(QString &value) override;
    bool checkNext(QString &value) override;
};

#endif // NUMBERVALIDATOR_H
