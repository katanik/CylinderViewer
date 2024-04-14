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

void CylinderWidget::initShaders()
{
    // Compile vertex shader
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vshader.vsh")){
        close();
    }

    // Compile fragment shader
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fshader.fsh")){
        close();
    }

    // Link shader pipeline
    if (!m_program.link()){
        close();
    }

    // Bind shader pipeline for use
    if (!m_program.bind()){
        close();
    }
}

void CylinderWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 0.0); // black background

    initShaders();
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
}
static void normalizeAngle(int &angle)
{
    while (angle < 0){
        angle += 360;
    }
    while (angle > 360){
        angle -= 360;
    }
}

void CylinderWidget::setXRotation(int angle)
{
    normalizeAngle(angle);
    const float radiantAngle = static_cast<float>(angle) / M_2_PI;
    if (radiantAngle != m_rotationAngles.x()) {
        m_rotationAngles.setX(angle);
        emit xRotationChanged(angle);
        update();
    }
}

void CylinderWidget::setYRotation(int angle)
{
    normalizeAngle(angle);
    const float radiantAngle = static_cast<float>(angle) / M_2_PI;
    if (radiantAngle != m_rotationAngles.y()) {
        m_rotationAngles.setY(angle);
        emit yRotationChanged(angle);
        update();
    }
}

void CylinderWidget::setZRotation(int angle)
{
    normalizeAngle(angle);
    const float radiantAngle = static_cast<float>(angle) / M_2_PI;
    if (radiantAngle != m_rotationAngles.z()) {
        m_rotationAngles.setZ(angle);
        emit zRotationChanged(angle);
        update();
    }
}

void CylinderWidget::setRed(int r)
{
    m_cylinderTraits.color.setRed(r);
    update();
}

void CylinderWidget::setGreen(int g)
{
    m_cylinderTraits.color.setGreen(g);
    update();
}

void CylinderWidget::setBlue(int b)
{
    m_cylinderTraits.color.setBlue(b);
    update();
}
