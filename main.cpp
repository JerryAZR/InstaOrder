#include "mainwindow.h"

#include <QApplication>
#include <QDateTime>

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    switch (type) {
    case QtDebugMsg:
#ifdef QT_DEBUG
        fprintf(stderr, "[FastJD][Debug] %lld: %s (%s:%u)\n", now, localMsg.constData(), file, context.line);
#endif
        break;
    case QtInfoMsg:
        fprintf(stderr, "[FastJD][Info] %lld: %s (%s:%u)\n", now, localMsg.constData(), file, context.line);
        break;
    case QtWarningMsg:
        fprintf(stderr, "[FastJD][Warning] %lld: %s (%s:%u)\n", now, localMsg.constData(), file, context.line);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "[FastJD][Critical] %lld: %s (%s:%u)\n", now, localMsg.constData(), file, context.line);
        break;
    case QtFatalMsg:
        fprintf(stderr, "[FastJD][Fatal] %lld: %s (%s:%u)\n", now, localMsg.constData(), file, context.line);
        break;
    }
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(messageHandler);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
