#include "trainingssummarytile.h"

TrainingsSummaryTile::TrainingsSummaryTile()
{
    setFrameStyle(0);
    setMaximumSize(350, 350);
    setMinimumSize(350, 350);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    int shift = 25;

    QLabel *labelTitle = new QLabel(tr("Records"), this);
    QFont font;
    font.setWeight(QFont::Bold);
    font.setPointSize(12);
    labelTitle->setFont(font);

    labelTitle->setGeometry(10, -10, 400, 50);

    QString styleSheet = QString("QLabel { color : gray; }");

    QLabel *labelRecordsDistanceText = new QLabel(tr("D (km)"), this);
    labelRecordsDistanceText->setToolTip(QString("Distance (km)"));
    labelRecordsDistanceText->setGeometry(10, -10+shift, 400, 50);
    labelRecordsDistanceText->setStyleSheet(styleSheet);

    QLabel *labelRecordsSbText = new QLabel(tr("SB"), this);
    labelRecordsSbText->setToolTip(QString("Season Best (hh:mm:ss)"));
    labelRecordsSbText->setGeometry(90, -10+shift, 400, 50);
    labelRecordsSbText->setStyleSheet(styleSheet);

    QLabel *labelRecordsPbText = new QLabel(tr("PB"), this);
    labelRecordsPbText->setToolTip(QString("Personal Best (hh:mm:ss)"));
    labelRecordsPbText->setGeometry(170, -10+shift, 400, 50);
    labelRecordsPbText->setStyleSheet(styleSheet);

    QLabel *labelRecordsWrText = new QLabel(tr("WR"), this);
    labelRecordsWrText->setToolTip(QString("World Record (hh:mm:ss)"));
    labelRecordsWrText->setGeometry(250, -10+shift, 400, 50);
    labelRecordsWrText->setStyleSheet(styleSheet);

    QFrame *line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setGeometry(10, 0+shift, 330, 50);

    updateTile();
    connect(MessageAgent::getInstance(), SIGNAL(profileChanged()), this, SLOT(updateTile()));
}

void TrainingsSummaryTile::updateTile()
{
    // This is time critical: Already 230 ms for 15 trainings. Need to write results to DB for reuse.
    QVector<Record> records = TrainingManager::getInstance()->getRecords();

    int initialY = 40;
    int incrementY = 20;
    for(int i=0; i<records.size(); i++) {
        QLabel *label1 = new QLabel(distanceToString(records[i].distance), this);
        QLabel *label2 = new QLabel(secondsToTimeString(records[i].yearBestDuration), this);
        QLabel *label3 = new QLabel(secondsToTimeString(records[i].personalBestDuration), this);
        QLabel *label4 = new QLabel(secondsToTimeString(records[i].worldRecordDuration), this);

        label1->setGeometry(10, initialY + i*incrementY, 400, 50);
        label2->setGeometry(90, initialY + i*incrementY, 400, 50);
        label3->setGeometry(170, initialY + i*incrementY, 400, 50);
        label4->setGeometry(250, initialY + i*incrementY, 400, 50);
    }
}

QString TrainingsSummaryTile::secondsToTimeString(double seconds)
{
    if(seconds == 0.)
        return QString("-");

    int h = 3600;
    int m = 60;

    int hour = seconds/h;
    int second = int(seconds) % h;
    int minute = second/m;
    second = second % m;
    QString sHour = QString("%1").arg(hour, 2, 10, QChar('0'));
    QString sMinute = QString("%1").arg(minute, 2, 10, QChar('0'));
    QString sSecond = QString("%1").arg(second, 2, 10, QChar('0'));

    return sHour + ":" + sMinute + ":" + sSecond;
}

QString TrainingsSummaryTile::distanceToString(double distance)
{
    if(distance == 42195.) {
        return QString("Marathon");
    }

    QLocale x = QLocale();
    return x.toString(distance/1000.,'f',1);
}
