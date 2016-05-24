#include "logger.h"

Logger::Logger(const char * fileName, QObject *parent) :
    QObject(parent)
{
    this->fileName = QString(fileName);
    this->gpsLog.setFileName(fileName);

    // Try to open the file
    this->logOpen = this->gpsLog.open(QIODevice::ReadWrite);
    if(this->logOpen){
        qDebug() << "File Opened successfully" << endl;
        this->gpsStream.setDevice(&this->gpsLog);
        this->gpsStream.setCodec("UTF-8");
    }
    else
        qDebug() << "Did not open a log file" << endl;
}

void Logger::logGPSCoords(const QString &coords){
    this->gpsStream << coords << endl;
}

Logger::~Logger(){
    this->gpsStream.flush();
    this->gpsLog.close();
}
