#include "trainingheaderswidget.h"

TrainingHeadersWidget::TrainingHeadersWidget()
{
    tileHeight = 140;
    tileWidth = 350;

    layout = new QVBoxLayout;
    setLayout(layout);
}

void TrainingHeadersWidget::setTiles()
{
    QVector<Training::Header> headers = TrainingManager::getInstance()->getHeaders();

    // Sort by time
    std::sort(headers.begin(), headers.end(), compare);

    // Remove all old entries
    for(int i=0; i<trainingHeaderTiles.size(); i++) {
        layout->removeWidget(trainingHeaderTiles[i]);
        delete trainingHeaderTiles[i];
    }
    trainingHeaderTiles.clear();

    for(int i=0; i<headers.size(); i++) {
        if(i != 0)
            addHorizontalLine();
        addTile(new TrainingHeaderTile(headers[i]));
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

void TrainingHeadersWidget::addHorizontalLine()
{
    QFrame *line;
    line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    layout->addWidget(line);
}

bool compare(Training::Header a, Training::Header b)
{
    return a.dateTime>b.dateTime;
}
