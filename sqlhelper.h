#ifndef SQLHELPER_H
#define SQLHELPER_H

#include "usersettings.h"
#include <QtSql>
#include <training.h>
#include <QVector>
#include <QtCore/QCoreApplication>
#include <QFileInfo>
#include "usersettings.h"
#include <QDir>
#include <QDateTime>

class SqlHelper
{
public:
    static SqlHelper *getInstance();
    struct Header {
        QDateTime dateTime;
        float distance = 0;
        float duration = 0;
        float speed = 0;
        float heartRate = 0;
        float rating = 0;
        float efficiency = 0.;
        QString file = "";
        int id = 0;
        bool isValid = false;
    };

    struct Section {
        QDateTime time;
        float duration = 0.;
        float distance = 0.;
        float heartRateBpm = 0.;
    };

    Header selectTrainingHeaderById(unsigned int id);
    QVector<Header> selectTrainingHeaders();
    void insertTrainingHeaders(QVector<Header>);

    QVector<Section> selectTrainingSections(QString);
    void insertTrainingSections(QString, QVector<Section>);

    QVector<Section> getTrainingSectionsById(unsigned int id);
private:
    SqlHelper();

    bool isDatabaseValid();
    void initialize();

    QString dbFile;

    QSqlDatabase database;


    static SqlHelper* instance;

    static QString databaseName;

    int dbVersion = 1;

};

#endif // SQLHELPER_H
