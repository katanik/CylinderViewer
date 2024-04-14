#ifndef CYLINDER_TRIANGULATION_H
#define CYLINDER_TRIANGULATION_H

#include <qopengl.h>

#include <QList>
#include <QVector3D>

struct PersistentCylinderParameters{
    const float radius{0.15f};
    const float height{0.5f};
    const int triangulationSectors{1000};
    const QVector3D axis{0.0, 0.0, 1.0};
};

class CylinderTriangulation
{
public:
    CylinderTriangulation();

    const GLfloat *constData() const;
    int count() const;
    int vertexCount() const;

private:
    void addTopPlaneTriangle(const QVector2D& firstPoint, const QVector2D& secondPoint, GLfloat z);
    void addBackPlaneTriangle(const QVector2D& firstPoint, const QVector2D& secondPoint, GLfloat z);
    void addCylinderSurfaceTriangles(const QVector2D& firstPoint, const QVector2D& secondPoint, GLfloat z);

    void appendSegmentPoints(GLfloat x, GLfloat y, GLfloat z, const QVector3D& n);
    void appendSegmentPoints(const QVector2D& xyCoords, GLfloat z, const QVector3D& n);
    void appendPoint(const QVector3D &coordinates);

private:
    QList<GLfloat> m_data;

    static PersistentCylinderParameters m_parameters;
};

#endif // CYLINDER_TRIANGULATION_H
