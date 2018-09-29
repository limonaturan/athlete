#ifndef TRAININGHEADERSCROLLAREA_H
#define TRAININGHEADERSCROLLAREA_H

#include <QScrollArea>
#include "trainingheaderswidget.h"
#include <QPalette>
#include <QPushButton>
#include <QSizePolicy>
#include <QVector>
#include <training.h>

class TrainingHeaderScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    TrainingHeaderScrollArea();

    void setTrainingHeaderTiles(QVector<Training::Header>);

private:
    TrainingHeadersWidget *trainingHeadersWidget;
};

#endif // TRAININGHEADERSCROLLAREA_H
