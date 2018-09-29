#ifndef TRAININGHEADERSWIDGET_H
#define TRAININGHEADERSWIDGET_H

#include <QWidget>
#include <QVector>

#include "trainingheadertile.h"
#include "training.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialog>
#include <algorithm>

bool compare(Training::Header, Training::Header);

class TrainingHeadersWidget : public QWidget
{
    Q_OBJECT

public:
    TrainingHeadersWidget();

    //void addTiles(QVector<TrainingHeaderTile>);
    void setTiles(QVector<Training::Header>);
    void addTile(TrainingHeaderTile*);

private:
    void updateWidget();
    int tileHeight;
    int tileWidth;




    QVBoxLayout *layout;
    QVector<TrainingHeaderTile*> trainingHeaderTiles;
};

#endif // TRAININGHEADERSWIDGET_H
