#include "trainingheaderscrollarea.h"

TrainingHeaderScrollArea::TrainingHeaderScrollArea()
{
    trainingHeadersWidget = new TrainingHeadersWidget();

    QPalette palette;
    palette.setColor(QPalette::Foreground, Qt::black);
    setPalette(palette);

    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    setWidget(trainingHeadersWidget);
    this->resize(400,800);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}

void TrainingHeaderScrollArea::setTrainingHeaderTiles(QVector<Training::Header> headers)
{
    trainingHeadersWidget->setTiles(headers);
}
