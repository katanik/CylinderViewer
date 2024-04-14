#include "cylinder_widget.h"

#include <QCoreApplication>
#include <QMouseEvent>
#include <QOpenGLShaderProgram>

CylinderWidget::CylinderWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{}

CylinderWidget::~CylinderWidget(){
    makeCurrent();
    doneCurrent();
}

void CylinderWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 0.0); // black background

}

void CylinderWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

}

void CylinderWidget::resizeGL(int w, int h)
{
}

void CylinderWidget::mousePressEvent(QMouseEvent *event)
{
}

void CylinderWidget::mouseMoveEvent(QMouseEvent *event)
{
void CylinderWidget::setXRotation(int angle)
{
}

void CylinderWidget::setYRotation(int angle)
{
}

void CylinderWidget::setZRotation(int angle)
{
}

void CylinderWidget::setRed(int r)
{
}

void CylinderWidget::setGreen(int g)
{
}

void CylinderWidget::setBlue(int b)
{
}
