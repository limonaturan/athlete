#include "worldrecords.h"

WorldRecords::WorldRecords()
{
    UserSettings::profile p = UserSettings::getInstance()->getCurrentProfile();

    if(p.activity == UserSettings::Running) {
        records = {
            WorldRecord(   100.,      9.58),
            WorldRecord(   200.,     19.19),
            WorldRecord(   400.,     43.03),
            WorldRecord(   800.,    100.91),
            WorldRecord(  1000.,    131.96),
            WorldRecord(  1500.,    206.00),
            WorldRecord(  2000.,    284.79),
            WorldRecord(  3000.,    440.67),
            WorldRecord(  5000.,    757.35),
            WorldRecord( 10000.,   1577.53),
            WorldRecord( 20000.,   3386.00),
            WorldRecord( 30000.,   5207.40),
            WorldRecord( 42195.,   7299.00),
            WorldRecord(100000.,  22413.00)
        };
    }
    else {
        //TODO implementation for swimming and riding
    }
}

QVector<WorldRecord> WorldRecords::getRecords()
{
    return records;
}

QVector<double> WorldRecords::getDistances()
{
    QVector<double> v;
    for(int i=0; i<records.size(); i++) {
        v.append(records[i].distance/1000.);
    }
    return v;
}

QVector<double> WorldRecords::getDurations()
{
    QVector<double> v;
    for(int i=0; i<records.size(); i++) {
        v.append(records[i].duration);
    }
    return v;
}

QVector<double> WorldRecords::getSpeeds()
{
    QVector<double> v;
    for(int i=0; i<records.size(); i++) {
        v.append(records[i].distance / records[i].duration*3.6);
    }
    return v;
}
