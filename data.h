#ifndef DATA_H
#define DATA_H

#include <QVector>
#include <QString>
#include <QDateTime>

class Data
{
public:
    Data();

    QVector<float> x;
    QVector<float> y;

    struct Header {
        QDateTime dateTime;
        float distance = 0;
        float duration = 0;
        float speed = 0;
        float heartRate = 0;
        float rating = 0;
        float efficiency = 0.;
        QString file = "";
        int id = 0;
        bool isValid = false;
    };

    struct TrackPoint {
        QDateTime time;
        float latitudeDegrees;
        float longitudeDegrees;
        float altitudeMeters;
        float distanceMeters;
        float heartRateBpm;
        float speed;
        float runCadence;
    };

    struct Section {
        QDateTime time;
        float duration = 0.;
        float distance = 0.;
        float heartRateBpm = 0.;
    };

    struct Lap {
        QDateTime startTime;
        float totalTimeSeconds;
        float distanceMeters;
        float maximumSpeed;
        float calories;
        float averageHeartRateBpm;
        float maximumHeartRateBpm;
        float averageSpeed;
        QVector<TrackPoint> trackPoints;
    };

    struct Activity {
        QDateTime dateTime;
        float distance;
        float duration;
        float speed;
        float heartRate;
        float rating;
        int id;
        bool isValid = false;
        QVector<Lap> laps;
    };
};

#endif // DATA_H
