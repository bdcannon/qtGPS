#include "qtquick1applicationviewer.h"
#include <QApplication>
#include <QThread>
#include <QFile>
#include "gpsreader.h"
#include "logger.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Some threads to run so we don't block the ui
    QThread gpsThread;
    QThread loggerThread;

    // Set up the object to write the coordinates to file
    Logger logger("/home/pi/Documents/log.txt");
    logger.moveToThread(&loggerThread);

    // Set up the gps and a thread for it to live on
    GPSReader reader("/dev/ttyUSB0");
    reader.moveToThread(&gpsThread);

    QObject::connect(&reader, SIGNAL(rmcUpde(QString)), &logger, SLOT(logGPSCoords(QString)));

    gpsThread.start();
    reader.openPort();  // Opens the port and starts reading
    loggerThread.start();

    QtQuick1ApplicationViewer viewer;
    viewer.addImportPath(QLatin1String("modules"));
    viewer.setOrientation(QtQuick1ApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qrc:/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
