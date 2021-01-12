#ifndef IVALIDATOR_H
#define IVALIDATOR_H

#include <QString>

class iValidator{
public:
    virtual bool check(QString &value) = 0;
    virtual bool checkNext(QString &value) = 0;
};

#endif // IVALIDATOR_H
