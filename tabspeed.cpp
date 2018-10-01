#include "tabspeed.h"

TabSpeed::TabSpeed()
{
    plotSpeedDistance = new PlotSpeedDistance();
    plotSpeedDistance->updateGraph();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QGridLayout *settingsLayout = new QGridLayout;

    boxPersonalRecords = new QCheckBox(tr("Personal best"));
    boxWorldRecords    = new QCheckBox(tr("World records"));

    settingsLayout->addWidget(boxPersonalRecords, 1, 1);
    settingsLayout->addWidget(boxWorldRecords, 1, 2);

    mainLayout->addLayout(settingsLayout);
    mainLayout->addWidget(plotSpeedDistance);
    this->setLayout(mainLayout);

    connect(boxPersonalRecords, SIGNAL(released()), this, SLOT(onCheckPersonalBest()));
    connect(boxWorldRecords, SIGNAL(released()), this, SLOT(onCheckWorldRecords()));
}

void TabSpeed::updateGraph()
{
    plotSpeedDistance->updateGraph();
}

void TabSpeed::onCheckWorldRecords()
{
    plotSpeedDistance->toggleWorldRecords(boxWorldRecords->checkState());
}

void TabSpeed::onCheckPersonalBest()
{
    plotSpeedDistance->togglePersonalBest(boxPersonalRecords->checkState());
}
