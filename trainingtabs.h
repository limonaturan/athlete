#ifndef TRAININGTABS_H
#define TRAININGTABS_H

#include <QObject>
#include <QWidget>
#include <QTabWidget>
#include <QLabel>
#include <QString>
#include "plotspeeddistance.h"
#include "trainingmanager.h"

class TrainingTabs : public QTabWidget
{
    Q_OBJECT
public:
    TrainingTabs(TrainingManager*);
    void updateTabs();

    void setActivities(QVector<Training::Activity>);

private:
    TrainingManager *trainingManager;
    PlotSpeedDistance *plotSpeedDistance;

};

#endif // TRAININGTABS_H
