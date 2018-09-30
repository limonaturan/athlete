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

class TrainingManager
{
public:
    static TrainingManager *getInstance();
    TrainingManager();

    void setProfile(UserSettings::profile);

    QVector<Training::Header> getHeaders();


private:
    QVector<Training> trainings;
    UserSettings::profile profile;
    static TrainingManager *instance;

    void readAll();
};

#endif // TRAININGMANAGER_H
