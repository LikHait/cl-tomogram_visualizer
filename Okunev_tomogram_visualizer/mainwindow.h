#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bin.h"
#include "oglwidget.h"
#include <QMainWindow>
#include <QLabel>
#include <QSlider>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void fileLoad();

private slots:
    void OpenFile();
    void UseGPU();
    void currentLevelChanged(int currentValue);
    void minSliderChanged(int newMin);
    void residualSliderChanged(int newRes);
    void updateFPS(int FPS);
private:
    Ui::MainWindow *ui;
    QLabel* currentLevel;
    QLabel* countFPS;
};

#endif // MAINWINDOW_H
