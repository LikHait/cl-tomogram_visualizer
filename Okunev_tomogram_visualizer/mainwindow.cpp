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

    ui->horizontalSlider_max->setRange(0, 2000);
    ui->horizontalSlider_max->setValue(ui->openGLWidget->max);
    ui->label_current_max->setText(QString::number(ui->openGLWidget->max));

    connect(this, SIGNAL(fileLoad()), ui->openGLWidget, SLOT(updateView()));
    connect(ui->openGLWidget, SIGNAL(newFPS(int)), this, SLOT(updateFPS(int)));

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
        emit fileLoad();
    }
    else
    {
        msgBox.setText("Error");
    }
    msgBox.exec();
}

void MainWindow::UseGPU()
{
    if (ui->actionGPU->isChecked())
    {
        ui->openGLWidget->gpuChecked = true;
        ui->openGLWidget->needReload = true;
    }
    else
    {
        ui->openGLWidget->gpuChecked = false;
    }
    /*
    QMessageBox msgBox;
    msgBox.setText(QString::number(ui->openGLWidget->min));
    msgBox.exec();
    */
}

void MainWindow::currentLevelChanged(int value)
{
    currentLevel->setText("Current Level: " + QString::number(value));
    ui->openGLWidget->needReload = true;
}

void MainWindow::minSliderChanged(int newMin)
{
    ui->openGLWidget->min = newMin;
    ui->label_current_min->setText(QString::number(ui->openGLWidget->min));

    ui->openGLWidget->needReload = true;
}

void MainWindow::maxSliderChanged(int newMax)
{
    ui->openGLWidget->max = newMax;
    ui->label_current_max->setText(QString::number(newMax));

    ui->openGLWidget->needReload = true;
}

void MainWindow::updateFPS(int FPS)
{
    countFPS->setText("FPS: " + QString::number(FPS));

}


