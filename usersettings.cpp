#include "usersettings.h"

UserSettings* UserSettings::instance = 0;

UserSettings::UserSettings()
{
    filename = "settings.ats";
    indexOfProfile = 0;
    read();
}

void UserSettings::save()
{
    QFile file(filename);
    qDebug() << QDir::currentPath();
    if(!file.open(QIODevice::WriteOnly)) {
        return;
    }
    QTextStream stream(&file);
    stream << profiles.size() << endl;
    stream << indexOfProfile << endl;
    for(int i=0; i<profiles.size(); i++) {
        stream << profiles[i].name << "\t" << profiles[i].folder.absolutePath() << "\t" << profiles[i].activity << endl;
    }
    file.close();
}

UserSettings *UserSettings::getInstance()
{
    if(instance == 0) {
        instance = new UserSettings();
    }
    return instance;
}

bool UserSettings::addProfile(QString profileName, QString folder, QString activity, QLabel *message)
{
    if(getProfileNames().contains(profileName)) {
        message->setText("Profile already exists. Enter a unique profile name.");
        return false;
    }

    if(profileName == "") {
        message->setText("Enter a profile name.");
        return false;
    }

    if(!QDir(folder).exists()){
        message->setText("Folder does not exist. Enter a valid folder.");
        return false;
    }

    if(getFolders().contains(folder)){
        message->setText("Folder already assigned. Choose another folder.");
        return false;
    }

    if(folder == ""){
        message->setText("Enter a folder.");
        return false;
    }

    profile p;
    p.name = profileName;
    p.folder = QDir(folder);
    p.activity = activity;
    profiles.append(p);

    save();
    return true;
}

void UserSettings::chooseProfile(int index)
{
    indexOfProfile = index;
    save();
}

bool UserSettings::editProfile(int index, UserSettings::profile p, QLabel *message)
{
    if(getFolders().contains(p.folder.absolutePath()) || profiles[index].folder == p.folder) {
        message->setText("Folder already in use. Choose another folder.");
        return false;
    }

    profiles[index] = p;
    save();
    return true;
}

void UserSettings::deleteProfile(int index)
{
    if(index >= indexOfProfile)
        indexOfProfile -= 1;
    profiles.remove(index);
    save();
}

void UserSettings::read()
{
    profiles.clear();

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        return;
    }
    QTextStream stream(&file);
    QString lineNumberOfProfiles;
    if(!stream.atEnd())
        lineNumberOfProfiles = stream.readLine();
    else
        return;

    if(!stream.atEnd()) {
        QString sIndex = stream.readLine();
        indexOfProfile = sIndex.toInt();
    }
    else
        return;

    if(indexOfProfile < 0 && lineNumberOfProfiles.toInt() != 0)
        indexOfProfile = 0;

    profile p;
    for(int i=0; i<lineNumberOfProfiles.toInt(); i++) {
        QString line = stream.readLine();
        QStringList list = line.split("\t");
        if(list.size() != 3)
            continue;
        p.name = list[0];
        p.folder = QDir(list[1]);
        p.activity = list[2];
        profiles.append(p);
    }
    file.close();
}

QVector<QString> UserSettings::getPossibleActivities()
{
    QVector<QString> a;
    a.append("Running");
    a.append("Riding");
    a.append("Swimming");
    return a;
}

QVector<QString> UserSettings::getFolders()
{
    QVector<QString> folders;
    for(int i=0; i<profiles.size(); i++) {
        folders.append(profiles[i].folder.absolutePath());
    }
    return folders;
}

UserSettings::profile UserSettings::getProfile(int i)
{
    return profiles[i];
}

UserSettings::profile UserSettings::getCurrentProfile()
{
    return profiles[indexOfProfile];
}

QString UserSettings::getActivity(int i)
{
    return profiles[i].activity;
}

QString UserSettings::getFolder(int i)
{
    return profiles[i].folder.absolutePath();
}

int UserSettings::getActivityIndex(QString activity)
{
    if(activity == getPossibleActivities()[0])
        return 0;
    else if(activity == getPossibleActivities()[1])
        return 1;
    else if(activity == getPossibleActivities()[2])
        return 2;
    return 3;
}

QVector<QString> UserSettings::getProfileNames()
{
    QVector<QString> names;
    for(int i=0; i<profiles.size(); i++) {
        names.append(profiles[i].name);
    }
    return names;
}

