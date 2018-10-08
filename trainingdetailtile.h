#ifndef TRAININGDETAILTILE_H
#define TRAININGDETAILTILE_H

#include <QObject>
#include <QWidget>
#include "trainingmanager.h"
#include "training.h"
#include "messageagent.h"
#include <QGridLayout>
#include <QLabel>

class TrainingDetailTile : public QWidget
{
    Q_OBJECT
public:
    TrainingDetailTile();

private slots:
    void updateTraining();

private:
    QGridLayout *tableLayout;
    QLabel *labelDateText;
    QLabel *labelDistanceText;
    QLabel *labelDurationText;
    QLabel *labelDate;
    QLabel *labelDistance;
    QLabel *labelDuration;
};

#endif // TRAININGDETAILTILE_H
