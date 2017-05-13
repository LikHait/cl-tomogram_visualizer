#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class OGLWidget : public QOpenGLWidget, protected QOpenGLFunctions

{
     Q_OBJECT
private:
    int layerNumber;
    QColor TransverFunction(short value);
    int clamp(int val, int min, int max);
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

public:
    OGLWidget(QWidget *parent);
    void DrawQuads();
    int min = -1000;
    int max = 2000;
public slots:
    void levelChanged(int value);
    void updateOGL();
};

#endif // OGLWIDGET_H
