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
    double yMax = *std::max_element(y.constBegin(), y.constEnd())*1.1;

    if(this->graphCount() == 0)
        this->addGraph();
    this->graph(0)->clearData();
    this->graph(0)->setData(x,y);

    this->graph()->setLineStyle(QCPGraph::lsNone);
    this->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 6));

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

