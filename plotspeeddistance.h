#ifndef PLOTSPEEDDISTANCE_H
#define PLOTSPEEDDISTANCE_H

#include <QObject>
#include <QWidget>
#include "qcustomplot.h"
#include <QVector>
#include "training.h"
#include "trainingmanager.h"
#include <algorithm>
#include <QVBoxLayout>
#include <QGridLayout>
#include "plotdata.h"
#include <QColor>
#include <QPen>


class PlotSpeedDistance : public QCustomPlot
{
    Q_OBJECT
public:
    PlotSpeedDistance();

    void updateGraph();
    void toggleWorldRecords(bool);
    void togglePersonalBest(bool);

private slots:
    void onTrainingsChanged();

private:
    QVector<Training::Header> headers;
    TrainingManager *trainingManager;
    QCustomPlot *plot;
    QVBoxLayout *mainLayout;
    QGridLayout *settinsLayout;
    bool worldRecordsActive = 0;
    bool personalBestActive = 0;
};

#endif // PLOTSPEEDDISTANCE_H
