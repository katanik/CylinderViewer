#include <QApplication>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>

#include "window.h"
#include "cylinder_widget.h"

Window::Window()
{
    m_glWidget = new CylinderWidget;

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    QWidget* w = new QWidget;
    QVBoxLayout* container = new QVBoxLayout(w);

    constexpr QVector2D defaultAngles{30.0, 30.0};
    createRotationAnglesTool(*container, defaultAngles);

    constexpr QColor defaultColor{255, 255, 50};
    createColorTool(*container, defaultColor);

    mainLayout->addWidget(w, 0, Qt::AlignLeft);
    mainLayout->addWidget(m_glWidget, 1);

    setWindowTitle(tr("Cylinder viewer"));
}

void Window::createRotationAnglesTool(QVBoxLayout& toolContainer, const QVector2D& defaultAngles)
{
    toolContainer.addSpacerItem(new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Expanding));

    toolContainer.addWidget(new QLabel("Axis settings:"));

    auto addRotationAngleTool = [this, &toolContainer](float defaultValue, const auto& setter, const auto& signalFunc){
        auto spinBox = createAngleSpinBox();
        connect(spinBox, &QSpinBox::valueChanged, m_glWidget, setter);
        connect(m_glWidget, signalFunc, spinBox, &QSpinBox::setValue);
        toolContainer.addWidget(spinBox);
        spinBox->setValue(defaultValue);
    };

    toolContainer.addWidget(new QLabel("Rotate around Y axis"));
    addRotationAngleTool(defaultAngles.x(), &CylinderWidget::setXRotation, &CylinderWidget::xRotationChanged);

    toolContainer.addWidget(new QLabel("Rotate around Z axis"));
    addRotationAngleTool(defaultAngles.y(), &CylinderWidget::setYRotation, &CylinderWidget::yRotationChanged);

    toolContainer.addSpacerItem(new QSpacerItem(0, 30, QSizePolicy::Minimum, QSizePolicy::Minimum));
}

void Window::createColorTool(QVBoxLayout& toolContainer, const QColor& defaultColor)
{
    toolContainer.addWidget(new QLabel("Color settings:"));

    auto addColorTool = [this, &toolContainer](float defaultValue, const auto& setter){
        auto spinBox = createColorSpinBox();
        connect(spinBox, &QSpinBox::valueChanged, m_glWidget, setter);
        toolContainer.addWidget(spinBox);
        spinBox->setValue(defaultValue);
    };

    toolContainer.addWidget(new QLabel("Red"));
    addColorTool(defaultColor.red(), &CylinderWidget::setRed);

    toolContainer.addWidget(new QLabel("Green"));
    addColorTool(defaultColor.green(), &CylinderWidget::setGreen);

    toolContainer.addWidget(new QLabel("Blue"));
    addColorTool(defaultColor.blue(), &CylinderWidget::setBlue);

    toolContainer.addSpacerItem(new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

QSpinBox* Window::createAngleSpinBox()
{
    constexpr int maxAngle = 360;

    QSpinBox *spinbox = new QSpinBox();
    spinbox->setMinimum(0);
    spinbox->setMaximum(maxAngle);
    return spinbox;
}

QSpinBox* Window::createColorSpinBox()
{
    constexpr int maxColorValue = 255;

    QSpinBox *spinbox = new QSpinBox();
    spinbox->setMinimum(0);
    spinbox->setMaximum(maxColorValue);
    return spinbox;
}
