#ifndef GEOMETRY_ENGINE_H
#define GEOMETRY_ENGINE_H

#include <QColor>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include "cylinder_triangulation.h"

struct CylinderTraits{
    QColor color{0, 0, 0};
    const QVector3D lightPos{0, 0, -100}; // persistent in this app
};

class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine();
    virtual ~GeometryEngine();

    void drawCylinderGeometry(QOpenGLShaderProgram& program, const QMatrix4x4& mvpMatrix, const CylinderTraits& traits);

private:
    void setupVertexAttributes(QOpenGLShaderProgram& program);
    void initCylinderGeometry();

private:
    CylinderTriangulation m_cylinder;
    QOpenGLBuffer m_cylinderBuffer;
};

#endif // GEOMETRY_ENGINE_H
