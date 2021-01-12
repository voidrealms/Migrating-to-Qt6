#include <QCoreApplication>

/*

    What
    Chain of responsibility

    Description
    A way of passing a request between a chain of objects

    Why
    Single point of entry, very expandable

    Example
    Password compexity checker

    also use https://regex101.com/

 */


#include <QDebug>
#include "passwordvalidator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    PasswordValidator validator;
    QString password = "helloworld!@";
    bool passed = validator.check(password);
    qInfo() << "Passed: " << passed;

    return a.exec();
}
