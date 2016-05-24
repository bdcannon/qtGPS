#include "gpsreader.h"

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
        QStringList fields = line.split(',');
        if(fields.length() == 13){
            // RMC Update
            emit rmcUpde(fields);
            qDebug() << "RMC Update" << endl;
        }
    }
}
