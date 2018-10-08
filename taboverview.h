#ifndef TABOVERVIEW_H
#define TABOVERVIEW_H

#include <QObject>
#include <QWidget>
#include "profiletile.h"
#include <QGridLayout>
#include "trainingssummarytile.h"

class TabOverview : public QWidget
{
    Q_OBJECT
public:
    TabOverview();

private:
    ProfileTile *profileTile;
    TrainingsSummaryTile *trainingsSummaryTile;
    QGridLayout *layout;
};

#endif // TABOVERVIEW_H
