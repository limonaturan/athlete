#ifndef TRAININGHEADERTILE_H
#define TRAININGHEADERTILE_H

#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QString>
#include <QDateTime>
#include <QGridLayout>
#include <QPushButton>
#include <QFont>
#include <QDialog>
#include <QPushButton>
#include "training.h"
#include <QStyle>
#include <QPalette>
#include <QFrame>

class TrainingHeaderTile : public QFrame
{
Q_OBJECT

public:
    TrainingHeaderTile();
    //TrainingHeaderTile(Training::Header);
    void setData(Training::Header);



private:
    Training::Header header;

    QLabel *labelTitle;
    QLabel *labelDistanceName;
    QLabel *labelDurationName;
    QLabel *labelHeartRateName;
    QLabel *labelSpeedName;
    QLabel *labelRatingName;
    QLabel *labelEfficiencyName;

    QLabel *labelDistance;
    QLabel *labelDuration;
    QLabel *labelHeartRate;
    QLabel *labelSpeed;
    QLabel *labelRating;
    QLabel *labelDate;
    QLabel *labelEfficiency;

    QFont fontName;
    QFont fontValue;
    QFont fontTitle;

    //void setup();
};

#endif // TRAININGHEADERTILE_H
