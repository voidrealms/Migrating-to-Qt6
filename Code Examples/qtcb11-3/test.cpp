#include "test.h"

test::test(QObject *parent) : QObject(parent)
{

}

QString test::message()
{
    return m_message;
}

void test::setMessage(QString value)
{
 m_message = value;
 emit messageChanged(m_message);
}
