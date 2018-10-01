#include "plotspeeddistance.h"

PlotSpeedDistance::PlotSpeedDistance()
{
    trainingManager = TrainingManager::getInstance();
    wr = WorldRecords();
    //connect(trainingManager, SIGNAL(trainingsChanged()), this, SLOT(onTrainingsChanged()));
}

void PlotSpeedDistance::updateGraph()
{
    headers = trainingManager->getHeaders();
    if(headers.size() == 0)
        return;
    QVector<double> x, y;
    for(int i=0; i<headers.size(); i++) {
        x.append(headers[i].distance/1000.);
        y.append(headers[i].speed*3.6);
    }
    double yMaxPersonalBest, yMaxWorldRecord, yMax = 0.;
    double xMax = *std::max_element(x.constBegin(), x.constEnd())*1.1;
    yMax = *std::max_element(y.constBegin(), y.constEnd())*1.1;


    if(this->graphCount() == 0) {
        this->addGraph();
        this->addGraph();
        this->addGraph();
    }
    this->graph(0)->clearData();
    this->graph(1)->clearData();
    this->graph(2)->clearData();

    this->graph(0)->setData(x,y);

    if(personalBestActive) {
        PlotData fastestData = TrainingManager::getInstance()->getSpeedDistanceFastestSectionsAllTime();
        this->graph(1)->setData(fastestData.x,fastestData.y);
        yMaxPersonalBest = *std::max_element(fastestData.y.constBegin(), fastestData.y.constEnd())*1.1;
    }

    if(worldRecordsActive) {
        QVector<double> xR = wr.getDistances();
        QVector<double> yR = wr.getSpeeds();
        this->graph(2)->setData(xR, yR);
        yMaxWorldRecord = yR[0]*1.1;
    }

    if(yMaxPersonalBest > yMax)
        yMax = yMaxPersonalBest;
    if(yMaxWorldRecord > yMax)
        yMax = yMaxWorldRecord;

    this->graph(0)->setLineStyle(QCPGraph::lsNone);
    this->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 6));
    this->graph(0)->setPen(QPen(QColor(255, 40, 110, 255)));

    QPen penPersonalBest;
    penPersonalBest.setWidthF(4);
    penPersonalBest.setColor(QColor(255, 20, 70, 100));
    this->graph(1)->setLineStyle(QCPGraph::lsLine);
    this->graph(1)->setPen(penPersonalBest);

    QPen penRecords;
    penRecords.setWidthF(4);
    penRecords.setColor(QColor(230, 180, 10, 150));
    this->graph(2)->setLineStyle(QCPGraph::lsLine);
    this->graph(2)->setPen(penRecords);
    //this->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 6));

    this->xAxis->setLabel("Distance (km)");
    this->yAxis->setLabel("Speed (km/h)");
    this->xAxis->setRange(0, xMax);
    this->yAxis->setRange(0, yMax);
    this->replot();
}

void PlotSpeedDistance::toggleWorldRecords(bool active)
{
    worldRecordsActive = active;
    updateGraph();
}

void PlotSpeedDistance::togglePersonalBest(bool active)
{
    personalBestActive = active;
    updateGraph();
}

void PlotSpeedDistance::onTrainingsChanged()
{
    updateGraph();
}

