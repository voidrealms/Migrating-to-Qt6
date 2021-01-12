#include <QCoreApplication>
#include "worker.h"

//QNetworkAccessManager really encasulates the HTTP protocol, incudes SSL

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Worker worker;

    worker.get("https://postman-echo.com/get?foo1=bar1&foo2=bar2");


    QByteArray data;
    data.append("param1=hello");
    data.append("&");
    data.append("param2=foo");

    worker.post("https://postman-echo.com/post",data);


    return a.exec();
}
