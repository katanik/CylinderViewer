#ifndef CYLINDER_WIDGET_H
#define CYLINDER_WIDGET_H

#include <QWidget>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include <QMatrix4x4>

#include "geometry_engine.h"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class CylinderWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit CylinderWidget(QWidget *parent = nullptr);
    ~CylinderWidget();

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

    void setRed(int r);
    void setGreen(int g);
    void setBlue(int b);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

private:
    void initShaders();

private:
    QOpenGLShaderProgram m_program;
    std::unique_ptr<GeometryEngine> m_geomEngine = nullptr;

    CylinderTraits m_cylinderTraits;

    QVector3D m_rotationAngles;
    QVector2D m_lastPos;

    QMatrix4x4 m_projection;
};

#endif // CYLINDER_WIDGET_H
