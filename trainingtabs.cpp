#include "trainingtabs.h"

TrainingTabs::TrainingTabs()
{
    // First Tab
    tabOverview = new TabOverview;
    addTab(tabOverview, tr("Overview"));

    // Second Tab
    tabSpeed = new TabSpeed;
    tabSpeed->updateGraph();
    addTab(tabSpeed, tr("Speed"));
}

void TrainingTabs::updateTabs()
{
    tabSpeed->updateGraph();
}

void TrainingTabs::setActivities(QVector<Training::Activity>)
{

}
