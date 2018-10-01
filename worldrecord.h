#ifndef WORLDRECORD_H
#define WORLDRECORD_H

#include "usersettings.h"
#include <QVector>

class WorldRecord
{
public:
    WorldRecord();
    WorldRecord(float, float);

    float distance;
    float duration;
};

#endif // WORLDRECORD_H
