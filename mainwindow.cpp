#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << __LINE__ << "这条消息是在mainwindow中输出的qDebug";
    qInfo() << "这条消息是在mainwindow中输出的qInfo";
}

MainWindow::~MainWindow()
{
    delete ui;
}

