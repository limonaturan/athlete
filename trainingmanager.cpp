#include "trainingmanager.h"

TrainingManager* TrainingManager::instance = 0;

TrainingManager* TrainingManager::getInstance()
{
    if(instance == 0)
        instance = new TrainingManager();
    return instance;
}

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

PlotData TrainingManager::getSpeedDistanceFastestSectionsAllTime()
{
    PlotData data;
    for(int i=0; i<trainings.size(); i++) {
        QVector<Training::Section> bestSections = trainings[i].getBestSections();
        for(int j=0; j<bestSections.size(); j++) {
            float speed = bestSections[j].distance/bestSections[j].duration*3.6;
            if(data.x.size() > j && data.y[j] < speed) {
                data.y[j] = speed;
            }
            else if(data.x.size() <= j) {
                data.y.append(speed);
                data.x.append(bestSections[j].distance/1000.);
            }
        }
    }
    float speed = 0.;
    for(int i=data.x.size()-1; i>=0; i--) {
        if(data.y[i] > speed)
            speed = data.y[i];
        data.y[i] = speed;
    }

    return data;
}

void TrainingManager::setTrainingActive(int id, bool active)
{
    trainings[id].setActive(active);
    //TrainingManager::getInstance()->setTrainingActive(id, active);
}

void TrainingManager::setTrainingChecked(int id, bool checked)
{
    trainings[id].setChecked(checked);
}

void TrainingManager::readAll()
{
    trainings.clear();
    QDirIterator it(profile.folder.absolutePath(), QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString filename = it.next();
        if(QFileInfo(filename).isFile()) {
            Training t = Training(filename);
            if(t.getHeader().isValid)
                trainings.append(t);
        }

    }
}
