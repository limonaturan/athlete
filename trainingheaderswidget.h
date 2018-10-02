#ifndef TRAININGHEADERSWIDGET_H
#define TRAININGHEADERSWIDGET_H

#include <QWidget>
#include <QVector>

#include "trainingheadertile.h"
#include "trainingmanager.h"
#include "training.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialog>
#include <algorithm>
#include <QFrame>

bool compare(Training::Header, Training::Header);

class TrainingHeadersWidget : public QWidget
{
    Q_OBJECT

public:
    TrainingHeadersWidget();

    //void addTiles(QVector<TrainingHeaderTile>);
    void setTiles();
    void addTile(TrainingHeaderTile*);

private:
    void updateWidget();
    void addHorizontalLine();
    int tileHeight;
    int tileWidth;




    QVBoxLayout *layout;
    QVector<TrainingHeaderTile*> trainingHeaderTiles;
};

#endif // TRAININGHEADERSWIDGET_H
