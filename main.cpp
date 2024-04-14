#include "window.h"

#include <QApplication>
#include <QIcon>
#include <QScreen>
#include <QSize>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("Cylinder viewer");

    // Shows the app window with particular minimum size

    Window window;
    window.setWindowIcon(QIcon(":/images/icon.png"));
    window.setMinimumSize(QGuiApplication::primaryScreen()->size() * 0.5);
    window.show();

    return app.exec();
}
