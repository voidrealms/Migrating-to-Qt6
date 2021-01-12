#include "lengthvalidator.h"

LengthValidator::LengthValidator(QObject *parent) : QObject(parent)
{

}


bool LengthValidator::check(QString &value)
{
    qInfo()  << this << "Checking the length";
    if(value.length() < 8)
    {
        qInfo() << this << "Less than the required length!";
        return false;
    }
    return checkNext(value);
}

bool LengthValidator::checkNext(QString &value)
{
    if(children().length() == 0)
    {
        qInfo() << this << "No next validator!";
        return true;
    }

    iValidator* validator = dynamic_cast<iValidator*>(children().at(0));
    if(!validator)
    {
        qInfo() << this << "No castable next validator!";
        return false;
    }

    return validator->check(value);

}
