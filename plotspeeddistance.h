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


class PlotSpeedDistance : public QCustomPlot
{
    Q_OBJECT
public:
    PlotSpeedDistance(TrainingManager*);

    void updateGraph();

private slots:
    void onTrainingsChanged();

private:
    QVector<Training::Header> headers;
    TrainingManager *trainingManager;
    QCustomPlot *plot;
    QVBoxLayout *mainLayout;
    QGridLayout *settinsLayout;
};

#endif // PLOTSPEEDDISTANCE_H
