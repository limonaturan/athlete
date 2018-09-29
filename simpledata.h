#ifndef SIMPLEDATA_H
#define SIMPLEDATA_H

#include <QString>
#include <ctime>
#include <vector>
#include "spline.h"
#include <QDateTime>

class simpledata
{
public:
    simpledata(); // Konstruktor
    QString name; // Name der Trainingsstrecke
    unsigned long int distance; // Strecke in Metern
    unsigned long int duration; // Zeit in Sekunden
    QDateTime date; // Datum des Trainings
    QString activity; // Aktivität
    QString sex; // Geschlecht

    void setDistance(unsigned long int);
    void setDuration(unsigned long int);
    void setDate(QString);
    void setName(QString);
    void setActivity(QString);
    void setSex(QString);


    double performance(); // Leistung im Vergleich zum Weltrekord
    double h(); // Zeit in Stunden
    double min(); // Zeit in Minuten
    double km(); // Distance in km
    double pace(); // Tempo in Minuten pro Kilometer
    double speed(); // Geschwindigkeit in Kilometer pro Stunde

    QString performanceString(); // Leistung als QString
    QString dateString(); // Datum als QString

    QString timeString(); // Erzeugt einen String, der die Dauer der Aktivität zurückgibt
    unsigned long int secondsSinceTraining(); // Gibt die Anzahl der Sekunden seit Beginn des Trainings an bezüglich jetzt

};

#endif // SIMPLEDATA_H
