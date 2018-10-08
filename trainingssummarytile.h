#ifndef TRAININGSSUMMARYTILE_H
#define TRAININGSSUMMARYTILE_H

#include <QObject>
#include <QWidget>
#include <QFrame>
#include <QLabel>
#include "messageagent.h"
#include "training.h"
#include "trainingmanager.h"
#include <QSizePolicy>
#include <QScrollArea>
#include <QGridLayout>
#include <QFont>
#include <QDateTime>
#include <QLocale>
#include <QToolTip>

class TrainingsSummaryTile : public QFrame
{
    Q_OBJECT
public:
    TrainingsSummaryTile();

private slots:
    void updateTile();

private:
    QString secondsToTimeString(double seconds);
    QString distanceToString(double distance);

    QWidget *tableWidget;
};

#endif // TRAININGSSUMMARYTILE_H
