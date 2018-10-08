#include "taboverview.h"

TabOverview::TabOverview()
{
    layout = new QGridLayout;
    layout->setAlignment(Qt::AlignTop);
    setLayout(layout);

    profileTile = new ProfileTile;
    layout->addWidget(profileTile);

    trainingsSummaryTile = new TrainingsSummaryTile;
    layout->addWidget(trainingsSummaryTile);
}
