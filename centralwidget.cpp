#include "centralwidget.h"

CentralWidget::CentralWidget()
{
    mainLayout = new QHBoxLayout;
    trainingScrollArea = new TrainingHeaderScrollArea;
    trainingManager = TrainingManager::getInstance();

    trainingTabs = new TrainingTabs(trainingManager);

    mainLayout->addWidget(trainingScrollArea);
    mainLayout->addWidget(trainingTabs);

    onProfileChanged();

    setLayout(mainLayout);
}

void CentralWidget::onProfileChanged()
{
    // TrainingManager must read the trainings related to the chosen profile.
    trainingManager->setProfile(UserSettings::getInstance()->getCurrentProfile());

    // TrainingHeadersScrollArea must be updated.
    trainingScrollArea->setTrainingHeaderTiles(trainingManager->getHeaders());
}

void CentralWidget::updateCentralWidget()
{

}
