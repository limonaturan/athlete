#include "trainingtabs.h"

TrainingTabs::TrainingTabs(TrainingManager *tm)
{
    trainingManager = tm;

    plotSpeedDistance = new PlotSpeedDistance(trainingManager);
    plotSpeedDistance->updateGraph();

    addTab(plotSpeedDistance, tr("Speed"));

}

void TrainingTabs::updateTabs()
{
    plotSpeedDistance->updateGraph();
}

void TrainingTabs::setActivities(QVector<Training::Activity>)
{

}
