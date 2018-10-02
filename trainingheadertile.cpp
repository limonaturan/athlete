#include "trainingheadertile.h"

TrainingHeaderTile *TrainingHeaderTile::activeInstance = 0;

TrainingHeaderTile::TrainingHeaderTile()
{
    this->initialize();
}

TrainingHeaderTile::TrainingHeaderTile(Training::Header header)
{
    this->initialize();
    setData(header);
}

void TrainingHeaderTile::setData(Training::Header data)
{
    header = data;
    QFont font;
    font.setWeight(QFont::Bold);
    font.setPointSize(12);

    int h = 3600;
    int m = 60;

    int hour = header.duration/h;
    int second = int(header.duration) % h;
    int minute = second/m;
    second = second % m;
    QString sHour = QString("%1").arg(hour, 2, 10, QChar('0'));
    QString sMinute = QString("%1").arg(minute, 2, 10, QChar('0'));
    QString sSecond = QString("%1").arg(second, 2, 10, QChar('0'));

    QString sDuration = sHour + ":" + sMinute + ":" + sSecond;

    labelDate->setText(header.dateTime.toString("dd.MM.yyyy - HH:mm"));
    labelDistance->setText(QString::number(header.distance/1000., 'f', 2) + " km");
    labelDuration->setText(sDuration);
    labelHeartRate->setText(QString::number(header.heartRate, 'f', 2) + " bpm");
    labelSpeed->setText(QString::number(header.speed*3.6, 'f', 2) + " km/h");
    labelRating->setText(QString::number(header.rating, 'f', 2) + " %");
    labelEfficiency->setText(QString::number(header.rating*header.speed/header.heartRate*10, 'f', 2));

    labelDate->setFont(font);
    labelDate->setFixedHeight(19);
    labelDate->setFixedWidth(280);

}

void TrainingHeaderTile::setActive(bool active)
{
    if(!active)
        line->setStyleSheet("background-color: rgb(114, 194, 235);");
    else
        line->setStyleSheet("background-color: rgb(40, 240, 120);");
}

void TrainingHeaderTile::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        scribbling = true;
    }
}

void TrainingHeaderTile::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        scribbling = false;

        emit tileClicked();

        if(isChecked) {
            if(activeInstance == this) {
                isChecked = false;
                this->setActive(false);
                line->setVisible(false);
            }
            else {
                activeInstance->setActive(false);
                activeInstance = this;
                this->setActive(true);
            }
        }
        else {
            isChecked = true;
            if(activeInstance) {
                activeInstance->setActive(false);
            }
            activeInstance = this;
            this->setActive(true);
            line->setVisible(true);
        }
    }
}

void TrainingHeaderTile::onTileClicked()
{

}

void TrainingHeaderTile::initialize()
{
    connect(this, SIGNAL(tileClicked()), this, SLOT(onTileClicked()));
    fontTitle.setBold(false);
    fontTitle.setPointSize(12);

    QString styleSheetName = QString("QLabel { color : gray; }");

    labelTitle = new QLabel(this);
    labelDistanceName = new QLabel(this);
    labelDurationName = new QLabel(this);
    labelHeartRateName = new QLabel(this);
    labelSpeedName = new QLabel(this);
    labelRatingName = new QLabel(this);
    labelEfficiencyName = new QLabel(this);

    labelDistanceName->setStyleSheet(styleSheetName);
    labelDurationName->setStyleSheet(styleSheetName);
    labelHeartRateName->setStyleSheet(styleSheetName);
    labelSpeedName->setStyleSheet(styleSheetName);
    labelRatingName->setStyleSheet(styleSheetName);
    labelEfficiencyName->setStyleSheet(styleSheetName);

    labelDistance = new QLabel(this);
    labelDuration = new QLabel(this);
    labelHeartRate = new QLabel(this);
    labelSpeed = new QLabel(this);
    labelRating = new QLabel(this);
    labelDate = new QLabel(this);
    labelEfficiency = new QLabel(this);

    labelDate->setFont(fontTitle);

    labelDistanceName->setText(tr("Distance"));
    labelDurationName->setText(tr("Duration"));
    labelHeartRateName->setText(tr("Heart rate"));
    labelSpeedName->setText(tr("Speed"));
    labelRatingName->setText(tr("Rating"));
    labelEfficiencyName->setText(tr("Efficiency"));

    labelDate->setGeometry(10,10,320,50);
    labelDistanceName->setGeometry(10,18,400,50);
    labelDurationName->setGeometry(110,18,400,50);
    labelHeartRateName->setGeometry(10,63,400,50);
    labelSpeedName->setGeometry(220,18,400,50);
    labelRatingName->setGeometry(110,63,400,50);
    labelEfficiencyName->setGeometry(220,63,400,50);

    labelDistance->setGeometry(10,35,400,50);
    labelDuration->setGeometry(110,35,400,50);
    labelHeartRate->setGeometry(10,80,400,50);
    labelSpeed->setGeometry(220,35,400,50);
    labelRating->setGeometry(110,80,400,50);
    labelEfficiency->setGeometry(220,80,400,50);

    line = new QLabel(this);
    line->setVisible(false);
    line->setStyleSheet("background-color: rgb(114, 194, 235);"); // rgb(114, 194, 235)
    line->setGeometry(0,0,100,400);
    line->setFixedWidth(4);
    line->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    isChecked = false;
    isActive = false;
}
