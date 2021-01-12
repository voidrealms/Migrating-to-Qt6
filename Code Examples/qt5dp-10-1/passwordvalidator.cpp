#include "passwordvalidator.h"

PasswordValidator::PasswordValidator(QObject *parent) : QObject(parent)
{
    LengthValidator *lvalidator = new LengthValidator(this);
    NumberValidator *nvalidator = new NumberValidator(lvalidator);
    SpecialValidator *svalidator = new SpecialValidator(nvalidator);
    Q_UNUSED(svalidator);

}

bool PasswordValidator::check(QString &value)
{
    qInfo() << "Checking password";
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
