#include "sqlhelper.h"

SqlHelper* SqlHelper::instance = new SqlHelper();
QString SqlHelper::databaseName = "training.db";

SqlHelper* SqlHelper::getInstance()
{
    if(instance == 0) {
        instance = new SqlHelper();
    }
    return instance;
}

SqlHelper::SqlHelper()
{
    UserSettings *userSettings = UserSettings::getInstance();
    UserSettings::profile p = userSettings->getProfile(userSettings->indexOfProfile);

    dbFile = p.folder.absolutePath() + QDir::separator() + "training.db";

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
                "   ID         INTEGER AUTOINCREMENT, "
                "   FILENAME   TEXT,    "
                "   DATETIME   TEXT,    "
                "   DISTANCE   REAL,    "
                "   DURATION   REAL,    "
                "   HEARTRATE  REAL,    "
                "   RATING     REAL,    "
                "   EFFICIENCY REAL,    "
                "   PRIMARY KEY (ID))   ");

    res = query.exec(
                "CREATE TABLE TSTT ( "
                "   ID         INTEGER, "
                "   DISTANCE   REAL,    "
                "   DATETIME   TEXT,    "
                "   DURATION   REAL,    "
                "   HEARTRATE  REAL,    "
                "   PRIMARY KEY (ID, DISTANCE))   ");

    database.close();
}

bool SqlHelper::isDatabaseValid()
{
    QFileInfo f(dbFile);
    if(!(f.exists() && f.isFile()))
        return false;

    if(!database.open())
        return false;

    QVector<QString> expectedTableNames = {"THDR", "TSTT"};
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
    return true;
}
