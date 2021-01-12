#include "numbervalidator.h"

NumberValidator::NumberValidator(QObject *parent) : QObject(parent)
{

}

bool NumberValidator::check(QString &value)
{
    qInfo()  << this << "Checking the for numbers";
    //QRegExp regex;
    QRegularExpression regex;
    regex.setPattern("\\d"); // notice the double slash
    if(!value.contains(regex))
    {
        qInfo() << this << "Does not contain numbers!";
        return false;
    }

    return checkNext(value);
}

bool NumberValidator::checkNext(QString &value)
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
