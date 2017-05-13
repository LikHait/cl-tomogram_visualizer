#include "oglwidget.h"
#include "bin.h"
#include <QMessageBox>
#include <QString>
#include <QSurface>

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
}

void OGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor( 0.0f, 1.0f, 1.0f, 1.0f);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);

}

void OGLWidget::resizeGL(int width, int height)
{ 
    glLoadIdentity();
    glOrtho(0, Bin::X, 0, Bin::Y, -1, 1);
    glViewport(0, 0, width, height);
}

void OGLWidget::paintGL()
{
    DrawQuads();
   // SwapBuffers(???);
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
            glColor3i(col.red(), col.green(), col.blue());
            glVertex2i(x_coord, y_coord);
            //вершина 2
            value = Bin::array[x_coord + (y_coord + 1) * Bin::X + layerNumber * Bin::X * Bin::Y];
            col =  TransverFunction(value);
            glColor3i(col.red(), col.green(), col.blue());
            glVertex2i(x_coord, y_coord + 1);
            //вершина 3
            value = Bin::array[x_coord + 1 + (y_coord + 1) * Bin::X + layerNumber * Bin::X * Bin::Y];
            col =  TransverFunction(value);
            glColor3i(col.red(), col.green(), col.blue());
            glVertex2i(x_coord + 1, y_coord + 1);
            //вершина 4
            value = Bin::array[x_coord + 1 + y_coord * Bin::X + layerNumber * Bin::X * Bin::Y];
            col =  TransverFunction(value);
            glColor3i(col.red(), col.green(), col.blue());
            glVertex2i(x_coord + 1, y_coord);

       }
    glEnd();
}

void OGLWidget::levelChanged(int value)
{
    layerNumber = value;
}

void OGLWidget::updateOGL()
{
    paintGL();
}


