#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <QString>
#include <QVector>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDir>
#include <QDebug>
#include <QDate>

class UserSettings
{
public:
    static UserSettings *getInstance();

    struct profile {
        QString name;
        QDir folder;
        QString activity;
        QDate birthday;
    };

    static const QString Running;
    static const QString Swimming;
    static const QString Riding;

    bool addProfile(QString profile, QString folder, QString activity, QLabel *message);
    void chooseProfile(int index);
    bool editProfile(int index, profile p, QLabel *message);
    void deleteProfile(int index);
    int indexOfProfile;

    QVector<QString> getProfileNames();
    QVector<QString> getPossibleActivities();
    QVector<QString> getFolders();

    profile getProfile(int);
    profile getCurrentProfile();
    QString getActivity(int);
    QString getFolder(int);
    int getActivityIndex(QString);

    void save();

private:
    UserSettings();

    static UserSettings *instance;

    void read();

    QVector<profile> profiles;


    QString filename;
};

#endif // USERSETTINGS_H
