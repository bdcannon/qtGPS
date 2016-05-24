#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(const char * filename, QObject *parent = 0);
    ~Logger();
signals:
    void logOpened(const bool & opened);
public slots:
    void logGPSCoords(const QString & coords);
private :
    QFile gpsLog;
    QTextStream gpsStream;
    QString fileName;
    bool logOpen;
};

#endif // LOGGER_H
