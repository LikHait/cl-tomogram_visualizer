#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentLevel = new QLabel;
    ui->statusBar->addWidget(currentLevel, 0);
    currentLevel->setText("Current Level: 0");

    countFPS = new QLabel;
    ui->statusBar->addWidget(countFPS, 0);
    countFPS->setText("FPS: ");

    ui->horizontalSlider_min->setRange(-2000, 0);
    ui->horizontalSlider_min->setValue(ui->openGLWidget->min);
    ui->label_current_min->setText(QString::number(ui->openGLWidget->min));

    ui->horizontalSlider_residual->setRange(0, 4000);
    ui->horizontalSlider_residual->setValue(ui->openGLWidget->max - ui->openGLWidget->min);
    ui->label_current_residual->setText(QString::number(ui->openGLWidget->max - ui->openGLWidget->min));

/*
    tmr = new QTimer();
    tmr->setInterval(500);
    tmr->start();
    connect(tmr, SIGNAL(timeout()), ui->openGLWidget, SLOT(updateOGL()));
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OpenFile()
{
    QMessageBox msgBox;
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.bin");
    if (str != "")
    {
        Bin::readBIN(str);
        msgBox.setText("Ok. Opened " + str); //QString s = QString::number(i);
        ui->verticalSlider->setRange(0, Bin::Z - 1);
    }
    else
    {
        msgBox.setText("Error");
    }
    msgBox.exec();
}

void MainWindow::UseGPU()
{
    //отладка
    QMessageBox msgBox;
    msgBox.setText(QString::number(ui->openGLWidget->min));
    msgBox.exec();
}

void MainWindow::currentLevelChanged(int value)
{
    currentLevel->setText("Current Level: " + QString::number(value));
}

void MainWindow::minSliderChanged(int newMin)
{
    ui->openGLWidget->min = newMin;
    ui->label_current_min->setText(QString::number(ui->openGLWidget->min));
    //ui->horizontalSlider_residual->setValue(ui->openGLWidget->max - ui->openGLWidget->min);
    //ui->label_current_residual->setText(QString::number(ui->openGLWidget->max - ui->openGLWidget->min));
}

void MainWindow::residualSliderChanged(int newRes)
{
    ui->openGLWidget->max = newRes + ui->openGLWidget->min;
    ui->label_current_residual->setText(QString::number(newRes));
}
