#ifndef SQLHELPER_H
#define SQLHELPER_H

#include "usersettings.h"
#include <QtSql>
#include <training.h>
#include <QVector>
#include <QtCore/QCoreApplication>
#include <QFileInfo>

class SqlHelper
{
public:
    static SqlHelper *getInstance();

    Training::Header selectTrainingHeaderById(unsigned int id);
    QVector<Training::Header> selectTrainingHeaders();

    QVector<Training::Section> getTrainingSectionsById(unsigned int id);
private:
    SqlHelper();

    bool isDatabaseValid();
    void initialize();

    QSqlDatabase database;


    static SqlHelper* instance;

    static QString databaseName;

};

#endif // SQLHELPER_H
