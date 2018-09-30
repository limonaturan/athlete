#include "trainingtabs.h"

TrainingTabs::TrainingTabs()
{
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
