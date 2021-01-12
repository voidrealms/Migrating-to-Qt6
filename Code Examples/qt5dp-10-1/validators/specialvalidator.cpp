#include "specialvalidator.h"

SpecialValidator::SpecialValidator(QObject *parent) : QObject(parent)
{

}

bool SpecialValidator::check(QString &value)
{
    qInfo()  << this << "Checking for special chars";
    //QRegExp regex;
    QRegularExpression regex;
    regex.setPattern("\\W+"); // notice the double slash
    if(!value.contains(regex))
    {
        qInfo() << this << "Does not contain special chars!";
        return false;
    }

    return checkNext(value);
}

bool SpecialValidator::checkNext(QString &value)
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
