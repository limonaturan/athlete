#ifndef TABSPEED_H
#define TABSPEED_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include "plotspeeddistance.h"
#include <QCheckBox>

class TabSpeed : public QWidget
{
    Q_OBJECT
public:
    TabSpeed();

    void updateGraph();

private:
    QCheckBox *boxWorldRecords;
    QCheckBox *boxPersonalRecords;
    PlotSpeedDistance *plotSpeedDistance;

private slots:
    void onCheckWorldRecords();
    void onCheckPersonalBest();
};

#endif // TABSPEED_H
