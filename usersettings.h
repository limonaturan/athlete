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
#include <QObject>
#include <QWidget>

class UserSettings : public QWidget
{
    Q_OBJECT
public:
    static UserSettings *getInstance();

    struct profile {
        QString name;
        QDir folder;
        QString activity;
        QDate birthday;
    };

    bool addProfile(QString profile, QString folder, QString activity, QLabel *message);
    void chooseProfile(int index);
    bool editProfile(int index, profile p, QLabel *message);
    void deleteProfile(int index);
    int indexOfProfile;

    QVector<QString> getProfileNames();
    QVector<QString> getPossibleActivities();
    QVector<QString> getFolders();

    profile getProfile(int);
    QString getActivity(int);
    QString getFolder(int);
    int getActivityIndex(QString);

    void save();

signals:
    void profileChanged(UserSettings::profile);

private:
    UserSettings();

    static UserSettings *instance;

    void read();

    QVector<profile> profiles;


    QString filename;
};

#endif // USERSETTINGS_H
