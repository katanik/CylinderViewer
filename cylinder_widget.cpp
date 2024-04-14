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
    // Compiles vertex shader
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vshader.vsh")){
        close();
    }

    // Compiles fragment shader
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fshader.fsh")){
        close();
    }
}

void CylinderWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 0.0); // black background

    initShaders();

    m_geomEngine = std::make_unique<GeometryEngine>();
}

void CylinderWidget::paintGL()
{
    // Clears color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enables depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enables back face culling
    glEnable(GL_CULL_FACE);

    // Calculates model view transformation
    QMatrix4x4 transformation;
    transformation.rotate(QQuaternion::fromEulerAngles(m_rotationAngles));
    m_geomEngine->drawCylinderGeometry(m_program, m_projection * transformation, m_cylinderTraits);
}

void CylinderWidget::resizeGL(int w, int h)
{
    // Calculates aspect ratio
    float aspectRatio = static_cast<float>(w) / static_cast<float>(h ? h : 1);

    // Default view parameters
    constexpr float nearPlane = 0.01f, farPlane = 100.0, fov = 45.0;

    // Sets perspective projection
    m_projection.setToIdentity();
    m_projection.perspective(fov, aspectRatio, nearPlane, farPlane);

    // Moves camera position
    m_projection.translate(0, 0, -1);
}

void CylinderWidget::mousePressEvent(QMouseEvent *event)
{
    // Saves mouse press position
    m_lastPos = QVector2D(event->position());
}

void CylinderWidget::mouseMoveEvent(QMouseEvent *event)
{
    // Rotation axis is perpendicular to the mouse position difference vector, so
    // X movement will correspond to rotation around Z axis, and Y movement will correspond to rotation around Y axis
    QVector2D diff = QVector2D(event->position()) - m_lastPos;
    if (event->buttons()) {
        setXRotation(m_rotationAngles.x() + diff.y());
        setYRotation(m_rotationAngles.y() + diff.x());
    }
    m_lastPos = QVector2D(event->position());
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
