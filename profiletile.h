#ifndef PROFILETILE_H
#define PROFILETILE_H

#include <QObject>
#include <QWidget>
#include <QFrame>
#include <QLabel>
#include "usersettings.h"
#include <QVBoxLayout>
#include <QFont>
#include <QSizePolicy>
#include "messageagent.h"
#include <QDir>

class ProfileTile : public QFrame
{
    Q_OBJECT
public:
    ProfileTile();

private slots:
    void updateProfile();

private:
    QLabel *labelProfileName;
    QLabel *labelActivity;
    QLabel *labelNumberOfTrainings;
    QLabel *labelFolderText;
    QLabel *labelFolder;
    QLabel *labelProfileNameText;
    QLabel *labelActivityText;
    QLabel *labelNumberOfTrainingsText;
    QVBoxLayout *layout;
};

#endif // PROFILETILE_H
