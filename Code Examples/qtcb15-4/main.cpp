#include <QCoreApplication>
#include <QDebug>
#include <QDateTime>
#include <QTime>
#include <QDate>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDate today = QDate::currentDate();
    qInfo() << today;
    qInfo() << today.addDays(1);
    qInfo() << today.addYears(20);
    //qInfo() << today.toString(Qt::DateFormat::SystemLocaleDate);
    qInfo() << "ISO: " << today.toString(Qt::DateFormat::ISODate);
    qInfo() << "RFC: " << today.toString(Qt::DateFormat::RFC2822Date);
    qInfo() << "TXT: " << today.toString(Qt::DateFormat::TextDate);

    QTime now = QTime::currentTime();
    qInfo() << now;
    //qInfo() << now.toString(Qt::DateFormat::DefaultLocaleLongDate);
    //qInfo() << now.toString(Qt::DateFormat::DefaultLocaleShortDate);

    qInfo() << "ISO: " << now.toString(Qt::DateFormat::ISODate);
    qInfo() << "RFC: " << now.toString(Qt::DateFormat::RFC2822Date);
    qInfo() << "TXT: " << now.toString(Qt::DateFormat::TextDate);

    QDateTime current = QDateTime::currentDateTime();
    qInfo() << "current: " << current;

    QDateTime expire = current.addDays(45);
    qInfo() << "expire: " << expire;

    if(current > expire) {
        qInfo() << "Expired!";
    } else {
        qInfo() << "Not expired";
    }

    return a.exec();
}
