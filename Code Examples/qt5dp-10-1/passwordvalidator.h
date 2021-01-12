#ifndef PASSWORDVALIDATOR_H
#define PASSWORDVALIDATOR_H

#include <QObject>
#include <QDebug>
#include "interfaces/iValidator.h"
#include "validators/lengthvalidator.h"
#include "validators/numbervalidator.h"
#include "validators/specialvalidator.h"

class PasswordValidator : public QObject
{
    Q_OBJECT
public:
    explicit PasswordValidator(QObject *parent = nullptr);
    bool check(QString &value);
signals:

};

#endif // PASSWORDVALIDATOR_H
