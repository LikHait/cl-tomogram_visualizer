#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTime>
#include <QTimer>
#include <QTimerEvent>
#include <QImage>

class OGLWidget : public QOpenGLWidget, protected QOpenGLFunctions

{
     Q_OBJECT
private:
    int layerNumber;
    QColor TransverFunction(short value);
    int clamp(int val, int min, int max);
    bool BinLoad = false; //файл загружен
    int frameCount; //счетчик кадров
    QTime frameTime; //счетчик времени для fps

    int idleTimerId; //id идлера
    //текстуры
    GLuint VBOtexture;
    QImage textureImage;
    void Load2DTexture();
    void DrawTexture();
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void DrawQuads();
    void generateTextureImage();
public:
    OGLWidget(QWidget *parent);
    int min = -1000;
    int max = 2000;
    bool gpuChecked = false;
    bool needReload;
    void timerEvent(QTimerEvent* event)
       {
           if(event->timerId() == idleTimerId)
           {
               paintGL();
           }
       }
public slots:
    void levelChanged(int value);
    void updateOGL();
    void updateView();

signals:
    void newFPS(int fps);
};

#endif // OGLWIDGET_H
