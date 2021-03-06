#ifndef TRAINING_H
#define TRAINING_H

#include <QString>
#include <QFile>
#include "pugi/pugixml.hpp"
#include "pugi/pugiconfig.hpp"
#include <QDateTime>
#include <QVector>
#include <QDebug>
#include "worldrecord.h"
#include <QtMath>
#include "sqlhelper.h"
#include "worldrecords.h"

class Training
{
public:
    Training();
    Training(QString filename);

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

    Header getHeader();
    QVector<Section> getBestSections();
    int getYear();
    bool isActive();
    bool isChecked();

    void setActive(bool);
    void setChecked(bool);


private:
    void defineWorldRecords();
    QVector<WorldRecord> wrRunning;
    static int getNextID();
    static int id;
    bool active = false;
    bool checked = false;

    QVector<float> getDistancesForStatistics();


    static QString statisticsFolder;

    Activity readTcxFile(QString);
    pugi::xml_parse_result trainingData;
    QString filename;

    float getDistance();
    float getDuration();
    QDateTime getDateTime();
    float getHeartRate();
    float getSpeed();
    float getCadence();

    Header header;

    Activity getActivity();
    Activity activity;

};

#endif // TRAINING_H
