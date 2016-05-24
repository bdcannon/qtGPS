#include "gpsreader.h"

const char * GPSReader::RMC_ID = "$GPSRMC";

GPSReader::GPSReader(const char * port, QObject *parent) :
    QObject(parent)
{
    qDebug() << "GPSReader constuctor called" << endl;
    this->portOpen = false;

    // Set up some other port stuff
    this->gpsPort.setBaudRate(QSerialPort::Baud4800);
    this->gpsPort.setPortName(port);

    // Connect up some signals
    QObject::connect(&this->gpsPort, SIGNAL(readyRead()), this, SLOT(readLine()));
    QObject::connect(this, SIGNAL(rmcUpde(QString)), this, SLOT(printUpdate(QString)));

}

/**
 * @brief GPSReader::openPort attempts to open the port if the port is not
 * already open
 * @return bool if the port is open or not
 */
bool GPSReader::openPort(){
    this->portOpen = this->gpsPort.open(QSerialPort::ReadOnly);
    emit portStatusChange(this->portOpen);
    return this->portOpen;
}

/**
 * @brief GPSReader::readLine main entry point for handling data sent by the
 * gps unit
 */
void GPSReader::readLine(){
    if(this->gpsPort.canReadLine()){
        QString line = QString(gpsPort.readLine());
        if(line.startsWith("$GPRMC"))
            processLine(line);
    }
}

/**
 * @brief processLine Processes the line and outputs a nicely for
 * @param line line read from the gps
 * @return a formatted string for the GPS location
 */

void GPSReader::processLine(const QString & line){
    QStringList fields = line.split(',');
    QString time = fields[1];

    QString latitude = fields[3];
    QString latDirection = fields[4];

    QString longitude = fields[5];
    QString lonDirection = fields[6];

    QString decLat = convertToDecimal(latitude, latDirection);
    QString decLon = convertToDecimal(longitude, lonDirection);
    QString formatted = time + ',' + decLat + ',' + decLon;

    emit rmcUpde(formatted);
}

/**
 * @brief GPSReader::convertToDecimal Converts gps corrds from minutes and seconds to decimal
 * @param coord Raw coordinate read from the gps
 * @param dir Tells us if we should negate the value of the coord
 * @return the formatted decimial coord
 */
QString GPSReader::convertToDecimal(const QString & coord, const QString & dir){
    int decIndex = coord.indexOf('.');

    QString minutes = coord.mid(decIndex - 2);
    double dec = minutes.toDouble() * 60 / 3600;
    double degrees = coord.mid(0, decIndex -2).toDouble();
    double decCoord = dec + degrees;
    if(dir == "W" || dir == "S")
        decCoord *= -1.0;

    return QString::number(decCoord);
}


void GPSReader::printUpdate(const QString &update){
    qDebug() << update << endl;
}
