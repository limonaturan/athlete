#include "trainingheaderswidget.h"

TrainingHeadersWidget::TrainingHeadersWidget()
{
    tileHeight = 140;
    tileWidth = 350;

    layout = new QVBoxLayout;
    setLayout(layout);
}

void TrainingHeadersWidget::setTiles(QVector<Training::Header> headers)
{
    std::sort(headers.begin(), headers.end(), compare);

    for(int i=0; i<trainingHeaderTiles.size(); i++) {
        layout->removeWidget(trainingHeaderTiles[i]);
        delete trainingHeaderTiles[i];
    }
    trainingHeaderTiles.clear();

    for(int i=0; i<headers.size(); i++) {
        TrainingHeaderTile *tile = new TrainingHeaderTile;
        tile->setData(headers[i]);
        addTile(tile);
    }
    updateWidget();
}

void TrainingHeadersWidget::addTile(TrainingHeaderTile* tile)
{
    trainingHeaderTiles.append(tile);
    layout->addWidget(tile);
}

void TrainingHeadersWidget::updateWidget()
{
    int numberOfTiles = trainingHeaderTiles.size();
    setFixedSize(tileWidth, tileHeight*numberOfTiles);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    //show();
}

bool compare(Training::Header a, Training::Header b)
{
    return a.dateTime>b.dateTime;
}
