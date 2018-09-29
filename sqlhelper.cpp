#include "sqlhelper.h"

SqlHelper* SqlHelper::instance = 0;
QString SqlHelper::databaseName = "training.db";

SqlHelper* SqlHelper::getInstance()
{
    if(instance == 0) {
        instance = new SqlHelper();
    }
    return instance;
}

QVector<SqlHelper::Header> SqlHelper::selectTrainingHeaders()
{
    QVector<Header> headers;
    database.open(); //needed???
    QSqlQuery query;
    if(!query.exec("SELECT * FROM THDR WHERE PROFILE = " + UserSettings::getInstance()->getCurrentProfile().name))
        return headers;

    while(query.next()) {
        Header header;
        header.file       = query.value(1).toInt();
        header.id         = query.value(2).toInt();
        header.dateTime   = QDateTime::fromString(query.value(3).toString(), "yyyy-MM-ddTHH:mm:ss");
        header.distance   = query.value(4).toFloat();
        header.duration   = query.value(5).toFloat();
        header.heartRate  = query.value(6).toFloat();
        header.rating     = query.value(7).toFloat();
        header.efficiency = query.value(8).toFloat();
        headers.append(header);
    }

    return headers;
}

void SqlHelper::insertTrainingHeaders(QVector<Header> headers)
{
    database.open();
    QSqlQuery query;

    // TODO: Do multi insert. Yet don't know how to easily do this.
    for(int i=0; i<headers.size(); i++) {
        query.prepare("INSERT INTO THDR(PROFILE, FILENAME, ID, DATETIME, DISTANCE, DURATION, HEARTRATE, RATING, EFFICIENCY)"
                      "values(:PROFILE, :FILENAME, :ID, :DATETIME, :DISTANCE, :DURATION, :HEARTRATE, :RATING, :EFFICIENCY)");
        query.bindValue(":PROFILE",    UserSettings::getInstance()->getCurrentProfile().name);
        query.bindValue(":FILENAME",   headers[i].file);
        query.bindValue(":DATETIME",   headers[i].dateTime);
        query.bindValue(":DISTANCE",   headers[i].distance);
        query.bindValue(":DURATION",   headers[i].duration);
        query.bindValue(":HEARTRATE",  headers[i].heartRate);
        query.bindValue(":RATING",     headers[i].rating);
        query.bindValue(":EFFICIENCY", headers[i].efficiency);
        query.exec();

        if(!query.next())
            qDebug() << "Caution: Something went wrong while inserting the training header of file " + headers[i].file;
    }
}

QVector<SqlHelper::Section> SqlHelper::selectTrainingSections(QString filename)
{
    QVector<Section> sections;
    database.open();
    QSqlQuery query;

    QString queryString = "SELECT * FROM TSTT WHERE PROFILE  = '" + UserSettings::getInstance()->getCurrentProfile().name + "' AND FILENAME = '" + filename + "'";
    query.exec(queryString);
    qDebug() << query.lastError().text();

    while(query.next()) {
        Section section;
        section.distance       = query.value(2).toFloat();
        section.time           = QDateTime::fromString(query.value(3).toString(), "yyyy-MM-ddTHH:mm:ss");
        section.duration       = query.value(4).toFloat();
        section.heartRateBpm   = query.value(5).toFloat();
        sections.append(section);
    }

    return sections;
}

void SqlHelper::insertTrainingSections(QString filename, QVector<Section> sections)
{
    database.open();
    QSqlQuery query;

    // TODO: Do multi insert. Yet don't know how to easily do this.
    for(int i=0; i<sections.size(); i++) {
        query.prepare("INSERT INTO TSTT(PROFILE, FILENAME, DISTANCE, DATETIME, DURATION, HEARTRATE)"
                      "values(:PROFILE, :FILENAME, :DISTANCE, :DATETIME, :DURATION, :HEARTRATE)");
        query.bindValue(":PROFILE",    UserSettings::getInstance()->getCurrentProfile().name);
        query.bindValue(":FILENAME",   filename);
        query.bindValue(":DISTANCE",   sections[i].distance);
        query.bindValue(":DATETIME",   sections[i].time);
        query.bindValue(":DURATION",   sections[i].duration);
        query.bindValue(":HEARTRATE",  sections[i].heartRateBpm);
        bool queryValid = query.exec();

        qDebug() << query.lastError().text();

        if(!queryValid)
            qDebug() << "Caution: Something went wrong while inserting the training header of file " + filename;
    }
}

SqlHelper::SqlHelper()
{
    dbFile = UserSettings::getInstance()->getCurrentProfile().folder.absolutePath() + QDir::separator() + "training.db";

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setHostName("host");
    database.setDatabaseName(dbFile);
    database.setUserName("athlete");
    database.setPassword("password");

    if(!isDatabaseValid()) {
        qDebug() << "SqlHelper: Initialize database.";
        initialize();
    }

}

void SqlHelper::initialize()
{
    database.open();

    QSqlQuery query;
    int res = query.exec(
                "CREATE TABLE THDR ( "
                "   PROFILE    TEXT,    "
                "   FILENAME   TEXT,    "
                "   ID         INTEGER, "
                "   DATETIME   TEXT,    "
                "   DISTANCE   REAL,    "
                "   DURATION   REAL,    "
                "   HEARTRATE  REAL,    "
                "   RATING     REAL,    "
                "   EFFICIENCY REAL,    "
                "   PRIMARY KEY (PROFILE, FILENAME))   ");

    res = query.exec(
                "CREATE TABLE TSTT ( "
                "   PROFILE    TEXT,    "
                "   FILENAME   TEXT,    "
                "   DISTANCE   REAL,    "
                "   DATETIME   TEXT,    "
                "   DURATION   REAL,    "
                "   HEARTRATE  REAL,    "
                "   PRIMARY KEY (PROFILE, FILENAME, DISTANCE))   ");
    qDebug() << query.lastError().text();

    res = query.exec(
                "CREATE TABLE TDBV ( "
                "   VERSION    INTEGER, "
                "   PRIMARY KEY (VERSION))   ");

    database.close();
}

bool SqlHelper::isDatabaseValid()
{
    QFileInfo f(dbFile);
    if(!(f.exists() && f.isFile()))
        return false;

    if(!database.open())
        return false;

    QVector<QString> expectedTableNames = {"THDR", "TSTT", "TDBV"};
    QVector<QString> actualTableNames;
    QSqlQuery query;
    if(!query.exec("SELECT * FROM SQLITE_MASTER"))
        return false;

    while(query.next()) {
        actualTableNames.append(query.value(1).toString());
    }

    for(int i=0; i<expectedTableNames.size(); i++) {
        if(!actualTableNames.contains(expectedTableNames[i]))
            return false;
    }

    if(!query.exec("SELECT * FROM TDBV"))
        return false;
    int persistedDbVersion = -1;
    if(query.next())
        persistedDbVersion = query.value(0).toInt();

/*  TODO: Implement DB versioning.
    if(persistedDbVersion != dbVersion)
        return false;
*/
    return true;
}
