#include "logger.h"

QString logger::filename = QDir::currentPath() + QDir::separator() + "log.txt";
bool logger::logging = false;
static const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(nullptr);

logger::logger(QObject *parent) : QObject(parent)
{

}

void logger::attach()
{
    logger::logging = true;
    qInstallMessageHandler(logger::handler);

}

void logger::handler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if(logger::logging) {
        QString txt;
        switch (type) {
        case QtInfoMsg:
            txt = QString("Info: %1 in %2").arg(msg);
            break;
        case QtDebugMsg:
            txt = QString("Debug: %1").arg(msg);
            break;
        case QtWarningMsg:
            txt = QString("Warning: %1").arg(msg);
            break;
        case QtCriticalMsg:
            txt = QString("Critical: %1").arg(msg);
            break;
        case QtFatalMsg:
            txt = QString("Fatal: %1").arg(msg);
            break;
        }
        QFile file(logger::filename);
        if(file.open(QIODevice::WriteOnly | QIODevice::Append)) {
            QTextStream ts(&file);
           // ts << QDateTime::currentDateTime().toString() << " - " << txt << context.file << " line: " << context.line << endl;
            ts << QDateTime::currentDateTime().toString() << " - " << txt << context.file << " line: " << context.line << Qt::endl;
            ts.flush();
            file.close();
        }
    }

    (*QT_DEFAULT_MESSAGE_HANDLER)(type, context, msg);
}
