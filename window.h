#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QVBoxLayout>

QT_FORWARD_DECLARE_CLASS(QSlider)
QT_FORWARD_DECLARE_CLASS(QSpinBox)

class CylinderWidget;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

private:
    void createRotationAnglesTool(QVBoxLayout& toolContainer, const QVector2D& defaultAngles);
    void createColorTool(QVBoxLayout& toolContainer, const QColor& defaultColors);

private:
    QSpinBox* createAngleSpinBox();
    QSpinBox* createColorSpinBox();

    CylinderWidget* m_glWidget;
};

#endif
