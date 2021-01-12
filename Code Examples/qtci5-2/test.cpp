#include "test.h"

test::test(QObject *parent) : QObject(parent)
{
    qDebug() << this  << "Constructed";
}

void test::testing()
{
    qWarning() << "This is a test!!!";
}
