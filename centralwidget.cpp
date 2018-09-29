#include "centralwidget.h"

CentralWidget::CentralWidget()
{
    mainLayout = new QHBoxLayout;
    trainingScrollArea = new TrainingHeaderScrollArea;
    trainingManager = new TrainingManager;

    trainingTabs = new TrainingTabs(trainingManager);

    mainLayout->addWidget(trainingScrollArea);
    mainLayout->addWidget(trainingTabs);

    userSettings = UserSettings::getInstance();
    UserSettings::profile p = userSettings->getProfile(userSettings->indexOfProfile);
    onProfileChanged(p);

    setLayout(mainLayout);
}

void CentralWidget::updateWidget()
{

}

void CentralWidget::onProfileChanged(UserSettings::profile profile)
{
    this->profile = profile;
    trainingManager->setProfile(profile);
    updateCentralWidget();

}

void CentralWidget::updateCentralWidget()
{
    QVector<Training::Header> headers = trainingManager->getHeaders();
    trainingScrollArea->setTrainingHeaderTiles(headers);
}
