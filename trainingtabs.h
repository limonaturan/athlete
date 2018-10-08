#ifndef TRAININGTABS_H
#define TRAININGTABS_H

#include <QObject>
#include <QWidget>
#include <QTabWidget>
#include <QLabel>
#include <QString>
#include "plotspeeddistance.h"
#include "trainingmanager.h"
#include "tabspeed.h"
#include "taboverview.h"

class TrainingTabs : public QTabWidget
{
    Q_OBJECT
public:
    TrainingTabs();
    void updateTabs();

    void setActivities(QVector<Training::Activity>);

private:
    PlotSpeedDistance *plotSpeedDistance;
    TabSpeed *tabSpeed;
    TabOverview *tabOverview;

};

#endif // TRAININGTABS_H
