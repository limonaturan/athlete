#ifndef TRAININGHEADERTILE_H
#define TRAININGHEADERTILE_H

#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QString>
#include <QDateTime>
#include <QGridLayout>
#include <QPushButton>
#include <QFont>
#include <QDialog>
#include <QPushButton>
#include "training.h"
#include <QStyle>
#include <QPalette>
#include <QFrame>
#include <QMouseEvent>
#include <QPoint>
#include <trainingmanager.h>
#include "messageagent.h"

class TrainingHeaderTile : public QFrame
{
Q_OBJECT

public:
    TrainingHeaderTile();
    TrainingHeaderTile(Training::Header);
    void setData(Training::Header);
    void setActive(bool);
    void setChecked(bool);
    int getId();

signals:
    void tileClicked();
    void activeTileChanged();


protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void onTileClicked();

private:
    Training::Header header;
    void initialize();

    QLabel *labelTitle;
    QLabel *labelDistanceName;
    QLabel *labelDurationName;
    QLabel *labelHeartRateName;
    QLabel *labelSpeedName;
    QLabel *labelRatingName;
    QLabel *labelEfficiencyName;

    QLabel *labelDistance;
    QLabel *labelDuration;
    QLabel *labelHeartRate;
    QLabel *labelSpeed;
    QLabel *labelRating;
    QLabel *labelDate;
    QLabel *labelEfficiency;

    QFont fontName;
    QFont fontValue;
    QFont fontTitle;

    QLabel *line;

    bool scribbling;

    bool isChecked;
    bool isActive;
    static TrainingHeaderTile *activeInstance;

    //void setup();
};

#endif // TRAININGHEADERTILE_H
