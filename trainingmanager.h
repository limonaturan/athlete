#ifndef TRAININGMANAGER_H
#define TRAININGMANAGER_H

#include <QVector>
#include "usersettings.h"
#include "training.h"
#include <QDirIterator>
#include <QFile>
#include <QWidget>
#include <QObject>
#include <QStringList>
#include <QDebug>
#include <QFileInfo>

class TrainingManager : public QWidget
{
    Q_OBJECT
public:
    TrainingManager();

    void setProfile(UserSettings::profile);

    QVector<Training::Header> getHeaders();

signals:
    void trainingsChanged();


private:
    QVector<Training> trainings;
    UserSettings::profile profile;

    void readAll();
};

#endif // TRAININGMANAGER_H
