#include "oglwidget.h"
#include "bin.h"
#include <QMessageBox>
#include <QString>
#include <QImage>

OGLWidget::OGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    layerNumber = 0;
}

int OGLWidget::clamp(int val, int min, int max)
{
    return val > max ? max : val < min ? min : val;
}

QColor OGLWidget::TransverFunction(short value)
{
    int newVal = clamp((value - min) * 255 / (max - min), 0, 255);
    return QColor::fromRgb(newVal, newVal, newVal);
    //return QColor::fromRgb(255, 0, 255);
}

void OGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor( 0.0f, 1.0f, 1.0f, 1.0f);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    frameTime.start();
    idleTimerId = startTimer(0); //???
}

void OGLWidget::resizeGL(int width, int height)
{ 
    glLoadIdentity();
    glOrtho(0, Bin::X, 0, Bin::Y, -1, 1);
    glViewport(0, 0, width, height);
}

void OGLWidget::paintGL()
{
    if (gpuChecked)
    {
        if (needReload)
        {
            generateTextureImage();
            Load2DTexture();
            needReload = false;
        }
        DrawTexture();
    }
    else
    {
        DrawQuads();
    }
    ++frameCount;
    if (frameTime.elapsed() >= 1000)
    {
        //emit newFPS(frameCount);
        emit newFPS((int)(frameCount / ((double)frameTime.elapsed()/1000.0)));
        frameCount = 0;
        frameTime.restart();
    }
    update();
}

void OGLWidget::DrawQuads()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glBegin(GL_QUADS);
    for (int x_coord = 0; x_coord < Bin::X - 1; x_coord++)
        for (int y_coord = 0; y_coord < Bin::Y - 1; y_coord++)
        {
            short value;
            QColor col;
            //вершина 1
            value = Bin::array[x_coord + y_coord * Bin::X + layerNumber * Bin::X * Bin::Y];
            col =  TransverFunction(value);
            glColor3f(col.redF(), col.greenF(), col.blueF());
            glVertex2i(x_coord, y_coord);
            //вершина 2
            value = Bin::array[x_coord + (y_coord + 1) * Bin::X + layerNumber * Bin::X * Bin::Y];
            col =  TransverFunction(value);
            glColor3f(col.redF(), col.greenF(), col.blueF());
            glVertex2i(x_coord, y_coord + 1);
            //вершина 3
            value = Bin::array[x_coord + 1 + (y_coord + 1) * Bin::X + layerNumber * Bin::X * Bin::Y];
            col =  TransverFunction(value);
            glColor3f(col.redF(), col.greenF(), col.blueF());
            glVertex2i(x_coord + 1, y_coord + 1);
            //вершина 4
            value = Bin::array[x_coord + 1 + y_coord * Bin::X + layerNumber * Bin::X * Bin::Y];
            col =  TransverFunction(value);
            glColor3f(col.redF(), col.greenF(), col.blueF());
            glVertex2i(x_coord + 1, y_coord);

       }
    glEnd();
}

void OGLWidget::updateView()
{
    //BinLoad = true;
    //resizeGL(this->width(), this->height());
    /*QMessageBox msg;
    msg.setText("j");
    msg.exec();     */
    glOrtho(0, Bin::X, 0, Bin::Y, -1, 1);
    glViewport(0, 0, this->width(), this->height());
    paintGL();
    update();
}

void OGLWidget::levelChanged(int value)
{
    layerNumber = value;
    paintGL();
}
/*
void OGLWidget::updateOGL()
{
    paintGL();
}
*/
void OGLWidget::Load2DTexture()
{
    //glGenTextures(1, &VBOtexture);
    glBindTexture(GL_TEXTURE_2D, VBOtexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureImage.width(), textureImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //glBindTexture( GL_TEXTURE_2D, 0);
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        QMessageBox msg;
        msg.setText(QString::number(err));
        msg.exec();
    }
}

void OGLWidget::generateTextureImage()
{
    QImage img(Bin::X, Bin::Y, QImage::Format_RGB32);
    for (int i = 0; i < Bin::X; ++i)
        for (int j = 0; j < Bin::Y; ++j)
        {
            int pixelNumber = i + j * Bin::X + layerNumber * Bin::X * Bin::Y;
            img.setPixel(i, j, TransverFunction(Bin::array[pixelNumber]).rgb());
        }
    textureImage = img;
}

void OGLWidget::DrawTexture()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, VBOtexture);

    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2i(0, 0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2i(0, Bin::Y);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2i(Bin::X, Bin::Y);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2i(Bin::X, 0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
