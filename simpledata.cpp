#include "simpledata.h"


simpledata::simpledata()
{
    name = "";
    distance = 0;
    duration = 0;
    date = QDateTime::fromString("1900-01-01 00:00", "yyyy-MM-dd HH:mm");
    sex = "male";
    activity = "";
}

void simpledata::setDistance(unsigned long int d) {
    distance = d;
}

void simpledata::setDuration(unsigned long int dur) {
    duration = dur;
}

void simpledata::setName(QString n) {
    name = n;
}

void simpledata::setDate(QString dt) {
    date = QDateTime::fromString(dt, "yyyy-MM-dd/HH:mm");
}

void simpledata::setActivity(QString a) {
    activity = a;
}

void simpledata::setSex(QString s) {
    sex = s;
}

double simpledata::h() {
    return duration/3600.;
}

double simpledata::min() {
    return duration/60.;
}

double simpledata::km() {
    return distance/1000.;
}

double simpledata::pace() {
    return (duration/60.)/(distance/1000.);
}

double simpledata::speed() {
    return distance/1000./(duration/3600.);
}

QString simpledata::timeString() {
    unsigned long int h = int(duration) / 3600;
    unsigned long int m = int(duration) / 60 - 60*h;
    unsigned long int s = int(duration) -h*3600 -m*60;
    if (h > 0 ) {
        QString hh = QString("%1").arg(h, 2, 10, QChar('0'));
        QString mm = QString("%1").arg(m, 2, 10, QChar('0'));
        QString ss = QString("%1").arg(s, 2, 10, QChar('0'));
        QString str = hh + ":" + mm + ":" + ss;
        return str;
    }
    else if (m > 0) {
        QString mm = QString("%1").arg(m, 2, 10, QChar('0'));
        QString ss = QString("%1").arg(s, 2, 10, QChar('0'));
        QString str = mm + ":" + ss;
        return str;
    }
    else {
        QString ss = QString("%1").arg(s, 2, 10, QChar('0'));
        return ss;
    }
}


double simpledata::performance() {
    std::vector<double> X(15), Y(15);
    if ( sex == "male" ) {
        X[0] = 100; Y[0] = 9.58;
        X[1] = 200; Y[1] = 19.19;
        X[2] = 400; Y[2] = 43.18;
        X[3] = 800; Y[3] = 1*60+40.91;
        X[4] = 1000; Y[4] = 2*60+11.96;
        X[5] = 1500; Y[5] = 3*60+26;
        X[6] = 2000; Y[6] = 4*60+44.79;
        X[7] = 3000; Y[7] = 7*60+20.67;
        X[8] = 5000; Y[8] = 12*60+37.35;
        X[9] = 10000; Y[9] = 26*60+17.53;
        X[10] = 20000; Y[10] = 56*60+25.98;
        X[11] = 25000; Y[11] = 	1*3600+12*60+25.4;
        X[12] = 30000; Y[12] = 1*3600+26*60+47.4;
        X[13] = 42195; Y[13] = 2*3600+02*60+57;
        X[14] = 100000; Y[14] = 6*3600+13*60+33;
    }
    else {
        X[0] = 100; Y[0] = 10.49;
        X[1] = 200; Y[1] = 21.34;
        X[2] = 400; Y[2] = 47.60;
        X[3] = 800; Y[3] = 1*60+53.28;
        X[4] = 1000; Y[4] = 2*60+28.98;
        X[5] = 1500; Y[5] = 3*60+50.07;
        X[6] = 2000; Y[6] = 5*60+25.36;
        X[7] = 3000; Y[7] = 8*60+6.11;
        X[8] = 5000; Y[8] = 14*60+11.15;
        X[9] = 10000; Y[9] = 29*60+31.78;
        X[10] = 20000; Y[10] = 1*3600+05*60+26.6;
        X[11] = 25000; Y[11] = 1*3600+27*60+5.9;
        X[12] = 30000; Y[12] = 1*3600+45*60+50.0;
        X[13] = 42195; Y[13] = 2*3600+15*60+25;
        X[14] = 100000; Y[14] = 6*3600+33*60+11;
    }
    tk::spline s;
    s.set_points(X,Y);
    if (time == 0) {
        return 0;
    }
    else {
        return s(distance)/duration*100;
    }
}

unsigned long int simpledata::secondsSinceTraining() { // Mögliches Problem: Referenz JETZT verschiebt sich während Sortierung. Lösung: Übergene JETZT als festgesetztes Argument.
    return date.secsTo(QDateTime::currentDateTime());
}


QString simpledata::performanceString() {
    return QString::number(performance(), 'f', 1).replace(".", ",") + " %";
}


QString simpledata::dateString() {
    return date.toString("dd.MM.yyyy, HH:mm");
}
