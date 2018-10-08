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
    UserSettings::profile profile = UserSettings::getInstance()->getCurrentProfile();
    setProfile(profile);
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

Training *TrainingManager::getTraining(int id)
{
    for(int i=0; i<trainings.size(); i++) {
        if(trainings[i].getHeader().id == id)
            return &trainings[i];
    }
    Training *t = new Training();
    return t;
}

Training::Header TrainingManager::getActiveTrainingHeader()
{
    for(int i=0; i<trainings.size(); i++) {
        if(trainings[i].isActive())
            return trainings[i].getHeader();
    }
    Training::Header h;
    return h;
}

QVector<Training::Header> TrainingManager::getCheckedTrainingHeaders()
{
    QVector<Training::Header> th;
    for(int i=0; i<trainings.size(); i++) {
        if(trainings[i].isChecked())
            th.append(trainings[i].getHeader());
    }
    return th;
}

int TrainingManager::getNumberOfTrainings()
{
    return trainings.size();
}

double TrainingManager::getTotalDistance()
{
    double distance = 0.;
    for(int i=0; i<trainings.size(); i++) {
        distance += trainings[i].getHeader().distance;
    }
    return distance;
}

QVector<Record> TrainingManager::getRecords()
{
    QVector<Record> records;
    WorldRecords WR = WorldRecords();
    QVector<WorldRecord> worldRecords = WR.getRecords();
    int currentYear = QDate::currentDate().year();
    bool noFurtherDistance = false;

    for(int i=0; i<worldRecords.size(); i++) {
        Record r;
        bool distanceAccomplished = false;
        if(!noFurtherDistance) {
            for(int k=0; k<trainings.size(); k++) {
                QVector<Training::Section> bestSections = trainings[k].getBestSections();
                for(int m=0; m<bestSections.size(); m++) {
                    if(bestSections[m].distance == worldRecords[i].distance) {
                        int trainingYear = trainings[k].getYear();
                        if(!r.personalBestDuration || r.personalBestDuration > bestSections[m].duration) {
                            r.personalBestDuration = bestSections[m].duration;
                            distanceAccomplished = true;
                        }
                        if(currentYear == trainingYear && (!r.yearBestDuration || r.yearBestDuration > bestSections[m].duration)) {
                            r.yearBestDuration = bestSections[m].duration;
                            distanceAccomplished = true;
                        }
                        break;
                    }
                }
            }
        }
        r.distance = worldRecords[i].distance;
        r.worldRecordDuration = worldRecords[i].duration;
        records.append(r);
        if(!distanceAccomplished) {
            noFurtherDistance = true;
        }
    }
    return records;
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
    getTraining(id)->setActive(active);
}

void TrainingManager::setTrainingChecked(int id, bool checked)
{
    getTraining(id)->setChecked(checked);
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
