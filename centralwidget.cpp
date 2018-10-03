#include "centralwidget.h"

CentralWidget::CentralWidget()
{
    mainLayout = new QHBoxLayout;
    trainingScrollArea = new TrainingHeaderScrollArea;
    trainingManager = TrainingManager::getInstance();

    trainingTabs = new TrainingTabs();
    messageAgent = MessageAgent::getInstance();

    mainLayout->addWidget(trainingScrollArea);
    mainLayout->addWidget(trainingTabs);

    onProfileChanged();
    connect(messageAgent, SIGNAL(tileClicked()), this, SLOT(updateTabWidget()));
    setLayout(mainLayout);
}

void CentralWidget::onProfileChanged()
{
    // TrainingManager must read the trainings related to the chosen profile.
    trainingManager->setProfile(UserSettings::getInstance()->getCurrentProfile());

    // TrainingHeadersScrollArea must be updated.
    trainingScrollArea->setTrainingHeaderTiles(trainingManager->getHeaders());
    trainingTabs->updateTabs();
}

void CentralWidget::updateTabWidget()
{
    trainingTabs->updateTabs();
}

void CentralWidget::updateCentralWidget()
{

}
