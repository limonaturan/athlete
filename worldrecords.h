#ifndef WORLDRECORDS_H
#define WORLDRECORDS_H

#include "worldrecord.h"
#include "usersettings.h"
#include <QVector>

class WorldRecords
{
public:
    WorldRecords();
    QVector<WorldRecord> getRecords();
    QVector<double> getDistances();
    QVector<double> getDurations();
    QVector<double> getSpeeds();


private:
    QVector<WorldRecord> records;
};

#endif // WORLDRECORDS_H
