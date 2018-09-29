#include "trainingmanager.h"


TrainingManager::TrainingManager()
{

}

void TrainingManager::setProfile(UserSettings::profile profile)
{
    this->profile = profile;
    readAll();
}

QVector<Training::Header> TrainingManager::getHeaders()
{
    QVector<Training::Header> headers;
    for(int i=0;i<trainings.size(); i++) {
        headers.append(trainings[i].getHeader());
    }
    return headers;
}

void TrainingManager::readAll()
{
    QDirIterator it(profile.folder.absolutePath(), QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString filename = it.next();
        if(QFileInfo(filename).isFile())
            trainings.append(Training(filename));
    }
    trainingsChanged();
}
