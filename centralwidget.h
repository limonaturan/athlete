#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <trainingheaderscrollarea.h>
#include <QPalette>
#include <QPushButton>
#include <trainingtabs.h>
#include "usersettings.h"
#include "trainingmanager.h"
#include "messageagent.h"

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    CentralWidget();

public slots:
    void onProfileChanged();
    void updateTabWidget();

private:
    QHBoxLayout * mainLayout;
    TrainingHeaderScrollArea *trainingScrollArea;
    TrainingTabs *trainingTabs;
    UserSettings *userSettings;
    UserSettings::profile profile;
    TrainingManager *trainingManager;
    MessageAgent *messageAgent;


    void updateCentralWidget();
};

#endif // CENTRALWIDGET_H
