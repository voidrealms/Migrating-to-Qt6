#include "commandline.h"

CommandLine::CommandLine(QObject *parent, FILE *fileHandle) : QObject(parent), cin(fileHandle)
{

}

void CommandLine::monitor()
{
    while (true)
    {
        QString value = cin.readLine();
        emit command(value);
    }
}

