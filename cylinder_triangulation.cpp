#include "cylinder_triangulation.h"

PersistentCylinderParameters CylinderTriangulation::m_parameters = {};

CylinderTriangulation::CylinderTriangulation() {
    const int sectors = m_parameters.triangulationSectors;
    const auto& radius = m_parameters.radius;
    const auto& z = m_parameters.height / 2;

    GLfloat angle = 0.0;

    for (int i = 0; i < sectors; ++i) {
        const GLfloat x1 = radius  * qSin(angle);
        const GLfloat y1 = radius  * qCos(angle);

        angle = ((i + 1) * 2 * M_PI) / sectors;
        const GLfloat x2 = radius  * qSin(angle);
        const GLfloat y2 = radius  * qCos(angle);

        addTopPlaneTriangle(x1, y1, x2, y2, z);
        addBackPlaneTriangle(x1, y1, x2, y2, z);
    }
}

const GLfloat* CylinderTriangulation::constData() const
{
    return m_data.constData();
}

int CylinderTriangulation::count() const
{
    return m_data.size();
}

int CylinderTriangulation::vertexCount() const
{
    return m_data.size() / 6;
}

void CylinderTriangulation::appendPoint(GLfloat x, GLfloat y, GLfloat z)
{
    m_data.append(x);
    m_data.append(y);
    m_data.append(z);
}

void CylinderTriangulation::appendPoint(const QVector3D &coordinates)
{
    m_data.append(coordinates.x());
    m_data.append(coordinates.y());
    m_data.append(coordinates.z());
}

void CylinderTriangulation::addTopPlaneTriangle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat z)
{
    QVector3D n = QVector3D::normal(QVector3D(x1 - x2, y1 - y2, 0.0f), QVector3D(-x2, -y2, 0.0f));
    appendPoint(x2, y2, z);
    appendPoint(n);
    appendPoint(x1, y1, z);
    appendPoint(n);
    appendPoint(0.0, 0.0, z);
    appendPoint(n);
}

void CylinderTriangulation::addBackPlaneTriangle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat z)
{
    QVector3D n = QVector3D::normal(QVector3D(x2 - x1, y2 - y1, 0.0f), QVector3D(-x1, -y1, 0.0f));
    appendPoint(x1, y1, -z);
    appendPoint(n);
    appendPoint(x2, y2, -z);
    appendPoint(n);
    appendPoint(0.0, 0.0, -z);
    appendPoint(n);
}

