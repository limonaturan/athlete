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
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setHostName("host");
    database.setDatabaseName("training.db");
    database.setUserName("athlete");
    database.setPassword("password");

    if(!isDatabaseValid())
        initialize();
    else {
        qDebug() << "DB exists.";
    }
}

void SqlHelper::initialize()
{
    database.open();

    QSqlQuery query;
    int res = query.exec(
                "CREATE TABLE THDR ( "
                "   ID         INTEGER, "
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
    // Test how to commit.
}

bool SqlHelper::isDatabaseValid()
{
    QFileInfo f("training.db");
    if(!(f.exists() && f.isFile()))
        return false;

    if(!database.open())
        return false;

    QVector<QString> expectedTableNames = {"THDR", "TSTT"};
    QVector<QString> actualTableNames;
    QSqlQuery query;
    int res = query.exec("SELECT * FROM SQLITE_MASTER");

    while(query.next()) {
        actualTableNames.append(query.value(1).toString());
    }

    for(int i=0; i<expectedTableNames.size(); i++) {
        if(!actualTableNames.contains(expectedTableNames[i]))
            return false;
    }
    return true;
}
