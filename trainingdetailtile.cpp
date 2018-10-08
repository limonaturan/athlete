#include "trainingdetailtile.h"

TrainingDetailTile::TrainingDetailTile()
{
    QFont fontTitle;
    fontTitle.setBold(false);
    fontTitle.setPointSize(12);

    QString styleSheetName = QString("QLabel { color : gray; }");

    labelDateText = new QLabel(this);
    labelDistanceText = new QLabel(this);
    labelDurationText = new QLabel(this);
    labelDate = new QLabel(this);
    labelDistance = new QLabel(this);
    labelDuration = new QLabel(this);


    labelDateText->setStyleSheet(styleSheetName);
    labelDistanceText->setStyleSheet(styleSheetName);
    labelDurationText->setStyleSheet(styleSheetName);

    labelDateText->setText(tr("Date"));
    labelDistanceText->setText(tr("Distance"));
    labelDurationText->setText(tr("Duration"));

}

void TrainingDetailTile::updateTraining()
{

}
