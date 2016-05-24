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
    static const char * RMC_ID;
signals:
    void portStatusChange(const bool &portStatus);
    void rmcUpde(const QString & rmcList);
private slots:
    void readLine();
    void printUpdate(const QString & update);
public slots:
    bool openPort();
private:
    QSerialPort gpsPort;
    void processLine(const QString &line);
    QString convertToDecimal(const QString & coord, const QString & dir);
};

#endif // GPSREADER_H
