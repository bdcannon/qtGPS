#ifndef GPSREADER_H
#define GPSREADER_H

#include <QObject>
#include <QSerialPort>
#include <QString>
#include <QDebug>
#include <QStringList>

class GPSReader : public QObject
{
    Q_OBJECT
public:
    explicit GPSReader(const char * port , QObject *parent = 0);
    bool portOpen;
signals:
    void portStatusChange(const bool &portStatus);
    void rmcUpde(const QStringList & rmcList);
private slots:
    void readLine();
public slots:
    bool openPort();
private:
    QSerialPort gpsPort;
};

#endif // GPSREADER_H
