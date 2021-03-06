#ifndef TRAININGMANAGER_H
#define TRAININGMANAGER_H

#include <QVector>
#include "usersettings.h"
#include "training.h"
#include <QDirIterator>
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <QFileInfo>
#include "plotdata.h"
#include "data.h"
#include "record.h"
#include <QDate>

class TrainingManager
{
public:
    static TrainingManager *getInstance();
    TrainingManager();

    void setProfile(UserSettings::profile);

    QVector<Training::Header> getHeaders();
    Training *getTraining(int id);
    Training::Header getActiveTrainingHeader();
    QVector<Training::Header> getCheckedTrainingHeaders();
    int getNumberOfTrainings();
    double getTotalDistance();
    QVector<Record> getRecords();

    PlotData getSpeedDistanceFastestSectionsAllTime();

    void setTrainingActive(int id, bool active);
    void setTrainingChecked(int id, bool checked);

private:
    QVector<Training> trainings;
    UserSettings::profile profile;
    static TrainingManager *instance;

    void readAll();
};

#endif // TRAININGMANAGER_H
