#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QTime>
#include <QMessageBox>
#include <QTextStream>
#include <QMutex>
#include <QMutexLocker>

#define LOG_PATH "./debug/log.txt"
QMutex mutex;

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QMutexLocker mutexLocker(&mutex);

    QFile logFile(LOG_PATH);
    if (!logFile.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QMessageBox::warning(nullptr, "日志输出", "日志输出文件打开失败", QMessageBox::Ok);
        return ;
    }

    QTextStream logStream(&logFile);

    QString logTxt;
    switch (type)
    {
    case QtDebugMsg:
    {
        logTxt = QString("QtDebugMsg: %1 (%2:%3, %4)").arg(msg, context.file, QString::number(context.line), context.function);
        break;
    }
    case QtInfoMsg:
    {
        logTxt = QString("QtInfoMsg: %1 (%2:%3, %4)").arg(msg, context.file, QString::number(context.line), context.function);
        break;
    }
    case QtCriticalMsg:
    {
        logTxt = QString("QtCriticalMsg: %1 (%2:%3, %4)").arg(msg, context.file, QString::number(context.line), context.function);
        break;
    }
    case QtWarningMsg:
    {
        logTxt = QString("QtWarningMsg: %1 (%2:%3, %4)").arg(msg, context.file, QString::number(context.line), context.function);
        break;
    }
    case QtFatalMsg:
    {
        logTxt = QString("QtFatalMsg: %1 (%2:%3, %4)").arg(msg, context.file, QString::number(context.line), context.function);
        break;
    }
    }

    // 将消息写入日志文件
    logStream << logTxt << "\n";
    logStream.flush();  // 确保消息即时写入文件

    logFile.close();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(messageHandler);
    MainWindow w;
    w.show();
    return a.exec();
}
