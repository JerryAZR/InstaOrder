#include "mainwindow.h"

#include <QApplication>
#include <QDateTime>
#include <iostream>
#include <QFile>
#include <QTextStream>

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    const char *file = context.file ? context.file : "";
    QFile log("log.txt");
    log.open(QFile::Append);
    QTextStream out(&log);
    QByteArray localMsg = msg.toLocal8Bit();
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    switch (type) {
    case QtDebugMsg:
#ifdef QT_DEBUG
        std::cout << "[FastJD][Debug] " << now << " : " << localMsg.constData()
                  << " @ " << file << context.line << ":" << std::endl;
#endif
        break;
    case QtInfoMsg:
        std::cout << "[FastJD][Info] " << now << " : " << localMsg.constData() << std::endl;
        out << "[FastJD][Info] " << now << " : " << localMsg.constData() << Qt::endl;
        break;
    case QtWarningMsg:
        std::cout << "[FastJD][Warning] " << now << " : " << localMsg.constData() << std::endl;
        out << "[FastJD][Warning] " << now << " : " << localMsg.constData() << Qt::endl;
        break;
    case QtCriticalMsg:
        std::cout << "[FastJD][Critical] " << now << " : " << localMsg.constData() << std::endl;
        out << "[FastJD][Critical] " << now << " : " << localMsg.constData() << Qt::endl;
        break;
    case QtFatalMsg:
        std::cout << "[FastJD][Fatal] " << now << " : " << localMsg.constData() << std::endl;
        out << "[FastJD][Fatal] " << now << " : " << localMsg.constData() << Qt::endl;
        break;
    }
    log.close();
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(messageHandler);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
