#include "geometry_engine.h"

#include <QVector2D>
#include <QVector3D>

GeometryEngine::GeometryEngine()
{
    initializeOpenGLFunctions();

    // Generates VBO
    m_cylinderBuffer.create();

    // Initializes cylinder geometry and transfers it to VBO
    initCylinderGeometry();
}

GeometryEngine::~GeometryEngine()
{
    m_cylinderBuffer.destroy();
}

void GeometryEngine::setupVertexAttributes(QOpenGLShaderProgram& program)
{

    m_cylinderBuffer.bind();

    auto glFunctionsPtr = QOpenGLContext::currentContext()->functions();

    // Tells pipeline how to locate vertex position data

    const int vertexLocation = program.attributeLocation("vertex");
    glFunctionsPtr->glEnableVertexAttribArray(vertexLocation);
    glFunctionsPtr->glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);

    const int normalLocation = program.attributeLocation("normal");
    glFunctionsPtr->glEnableVertexAttribArray(normalLocation);
    glFunctionsPtr->glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));

    m_cylinderBuffer.release();
}

void GeometryEngine::drawCylinderGeometry(QOpenGLShaderProgram& program, const QMatrix4x4& mvpMatrix, const CylinderTraits& traits)
{
    program.bind();

    // Stores the vertex attribute bindings for the program
    setupVertexAttributes(program);

    // Setup matrices
    program.setUniformValue(program.uniformLocation("mvpMatrix"), mvpMatrix);
    program.setUniformValue(program.uniformLocation("normalMatrix"), mvpMatrix.normalMatrix());

    // Setup color
    const QColor& color = traits.color;
    const QVector3D colorVector{color.redF(), color.greenF(), color.blueF()};
    program.setUniformValue(program.uniformLocation("color"), colorVector);

    // Setup light position
    program.setUniformValue(program.uniformLocation("lightPos"), traits.lightPos);

    // Draws cylinder triangulation
    glDrawArrays(GL_TRIANGLES, 0, m_cylinder.vertexCount());

    program.release();
}

void GeometryEngine::initCylinderGeometry()
{
    // Setup cylinder triangulation vertex buffer object
    m_cylinderBuffer.create();
    m_cylinderBuffer.bind();
    m_cylinderBuffer.allocate(m_cylinder.constData(), m_cylinder.count() * sizeof(GLfloat));
}
