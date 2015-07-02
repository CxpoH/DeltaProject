#include "mainwindow.h"

#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(imgresource);

//    QSurfaceFormat surfformat;
//    surfformat.setSamples(4);
//    surfformat.setDepthBufferSize(24);
//    QSurfaceFormat::setDefaultFormat(surfformat);

    QApplication app(argc, argv);
    app.setApplicationName("Delta project");
    app.setApplicationVersion("0.0.1");

    MainWindow mwindow;
    mwindow.setWindowTitle("Delta project");
    mwindow.setWindowIcon(QIcon(":/images/DeltaBind-Icon1.png"));

    mwindow.show();

    return app.exec();
}
