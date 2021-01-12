#ifndef LENGTHVALIDATOR_H
#define LENGTHVALIDATOR_H

#include <QObject>
#include <QDebug>
#include "../interfaces/iValidator.h"

class LengthValidator : public QObject, public iValidator
{
    Q_OBJECT
public:
    explicit LengthValidator(QObject *parent = nullptr);

signals:


    // iValidator interface
public:
    bool check(QString &value) override;
    bool checkNext(QString &value) override;
};

#endif // LENGTHVALIDATOR_H
