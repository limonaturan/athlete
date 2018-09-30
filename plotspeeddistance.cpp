#include "plotspeeddistance.h"

PlotSpeedDistance::PlotSpeedDistance(TrainingManager *tm)
{
    trainingManager = tm;
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

    //double xMin = *std::min_element(x.constBegin(), x.constEnd())*0.9;
    double xMax = *std::max_element(x.constBegin(), x.constEnd())*1.1;
    //double yMin = *std::min_element(y.constBegin(), y.constEnd())*0.9;


    if(this->graphCount() == 0) {
        this->addGraph();
        this->addGraph();
    }
    this->graph(0)->clearData();
    this->graph(0)->setData(x,y);

    PlotData fastestData = TrainingManager::getInstance()->getSpeedDistanceFastestSectionsAllTime();
    this->graph(1)->clearData();
    this->graph(1)->setData(fastestData.x,fastestData.y);
    double yMax = *std::max_element(fastestData.y.constBegin(), fastestData.y.constEnd())*1.1;

    this->graph(0)->setLineStyle(QCPGraph::lsNone);
    this->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 6));

    this->graph(1)->setLineStyle(QCPGraph::lsLine);
    //this->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 6));

    this->xAxis->setLabel("Distance (km)");
    this->yAxis->setLabel("Speed (km/h)");
    this->xAxis->setRange(0, xMax);
    this->yAxis->setRange(0, yMax);
    this->replot();
}

void PlotSpeedDistance::onTrainingsChanged()
{
    updateGraph();
}

