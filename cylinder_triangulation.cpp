#include "cylinder_triangulation.h"

PersistentCylinderParameters CylinderTriangulation::m_parameters = {};

CylinderTriangulation::CylinderTriangulation() {
    const int sectors = m_parameters.triangulationSectors;
    const auto& radius = m_parameters.radius;
    const auto& z = m_parameters.height / 2;

    GLfloat angle = 0.0;

    // Cylinder is built along Z axis in its local system

    for (int i = 0; i < sectors; ++i) {
        // Calculates 2D coordinates for the next sector of the cylinder base and adds its triangules
        const QVector2D firstPoint {radius  * qSin(angle), radius  * qCos(angle)};

        angle = ((i + 1) * 2 * M_PI) / sectors;
        const QVector2D secondPoint {radius  * qSin(angle), radius  * qCos(angle)};

        // Adds triangles of the cylinder bases
        addTopPlaneTriangle(firstPoint, secondPoint, z);
        addBackPlaneTriangle(firstPoint, secondPoint, z);

        // Adds triangles of the cylinder surface
        addCylinderSurfaceTriangles(secondPoint, firstPoint, z);
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

void CylinderTriangulation::appendSegmentPoints(GLfloat x, GLfloat y, GLfloat z, const QVector3D& n)
{
    m_data.append(x);
    m_data.append(y);
    m_data.append(z);
    appendPoint(n);
}

void CylinderTriangulation::appendSegmentPoints(const QVector2D& xyCoords, GLfloat z, const QVector3D& n)
{
    m_data.append(xyCoords.x());
    m_data.append(xyCoords.y());
    m_data.append(z);
    appendPoint(n);
}

void CylinderTriangulation::appendPoint(const QVector3D& coordinates)
{
    m_data.append(coordinates.x());
    m_data.append(coordinates.y());
    m_data.append(coordinates.z());
}

void CylinderTriangulation::addTopPlaneTriangle(const QVector2D& firstPoint, const QVector2D& secondPoint, GLfloat z)
{
    QVector3D n = QVector3D::normal(QVector3D(firstPoint - secondPoint), QVector3D(-secondPoint));
    appendSegmentPoints(secondPoint, z, n);
    appendSegmentPoints(firstPoint, z, n);
    appendSegmentPoints(0.0, 0.0, z, n);
}

void CylinderTriangulation::addBackPlaneTriangle(const QVector2D& firstPoint, const QVector2D& secondPoint, GLfloat z)
{
    QVector3D n = QVector3D::normal(QVector3D(secondPoint - firstPoint), QVector3D(-firstPoint));
    appendSegmentPoints(firstPoint, -z, n);
    appendSegmentPoints(secondPoint, -z, n);
    appendSegmentPoints(0.0, 0.0, -z, n);
}

void CylinderTriangulation::addCylinderSurfaceTriangles(const QVector2D& firstPoint, const QVector2D& secondPoint, GLfloat z)
{
    QVector3D n = QVector3D::normal(QVector3D(0.0f, 0.0f, -0.1f), QVector3D(secondPoint - firstPoint));
    appendSegmentPoints(firstPoint, z, n);
    appendSegmentPoints(firstPoint, -z, n);
    appendSegmentPoints(secondPoint, z, n);

    appendSegmentPoints(secondPoint, -z, n);
    appendSegmentPoints(secondPoint, z, n);
    appendSegmentPoints(firstPoint, -z, n);
}
