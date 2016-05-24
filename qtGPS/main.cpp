#include "qtquick1applicationviewer.h"
#include <QApplication>
#include <QThread>
#include "gpsreader.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QThread gpsThread;

    QtQuick1ApplicationViewer viewer;
    viewer.addImportPath(QLatin1String("modules"));
    viewer.setOrientation(QtQuick1ApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qrc:/main.qml"));
    viewer.showExpanded();

    GPSReader reader("/dev/ttyUSB0");
    reader.moveToThread(&gpsThread);
    gpsThread.start();
    reader.openPort();  // Opens the port and starts reading


    return app.exec();
}
