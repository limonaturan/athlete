#include "training.h"

QString Training::statisticsFolder = "data";

Training::Training()
{

    defineWorldRecords();
}

Training::Training(QString filename)
{
    defineWorldRecords();
    id = getNextID();
    this->filename = filename;
    activity.isValid = false;
    readTcxFile(filename);
    getBestSections();
}

Training::Header Training::getHeader()
{
    if(!activity.isValid) {
        header.isValid = false;
        return header;
    }
    header.dateTime = activity.dateTime;
    header.distance = activity.distance;
    header.heartRate = activity.heartRate;
    header.speed = activity.speed;
    header.duration = activity.duration;
    header.rating = activity.rating;
    header.id = id;
    header.isValid = true;

    return header;
}

int Training::id = 0;

int Training::getNextID()
{
    id += 1;
    return id;
}

QVector<float> Training::getDistancesForStatistics()
{
    int numberOfDistances = floor(activity.distance/100.);
    QVector<float> distances;
    for(int i=1; i<=numberOfDistances; i++)
        distances.append(i*100);
    return distances;
}

QVector<Training::Section> Training::getBestSections()
{
    QVector<Section> bestSections;

    if(!activity.isValid) // Do not proceed if there is no valid training data available.
        return bestSections;

    bestSections = readBestSections(); // Read persisted stratistics data
    if(bestSections.size() != 0)
        return bestSections;

    // Do statistics analysis
    QVector<float> distances = getDistancesForStatistics();

    QDateTime a = QDateTime::currentDateTime();

    for(int i=0; i<distances.size(); i++) {
        Section s;
        s.distance = distances[i];
        float distanceTemp = 0.;
        float durationTemp = 0.;
        float heartRateTemp = 0.;
        int numberOfDataPoints = 0;
        float distanceZero = 0.;
        QDateTime dtZero = activity.laps[0].trackPoints[0].time;
        for(int m=0; m<activity.laps.size(); m++) {
            for(int n=0; n<activity.laps[m].trackPoints.size(); n++) {
                for(int g=n; g<activity.laps[m].trackPoints.size(); g++) {
                    distanceTemp = activity.laps[m].trackPoints[g].distanceMeters - distanceZero;
                    durationTemp = float(dtZero.time().msecsTo(activity.laps[m].trackPoints[g].time.time()))/1000.;
                    numberOfDataPoints += 1;
                    if(distanceTemp - distances[i] > 0.) {
                        if(numberOfDataPoints > 5) {
                            durationTemp = durationTemp*distances[i]/distanceTemp;
                            if(s.duration == 0 || durationTemp < s.duration) {
                                s.duration = durationTemp;
                                s.heartRateBpm = heartRateTemp;
                            }
                        }
                        distanceTemp = 0.;
                        durationTemp = 0.;
                        heartRateTemp = 0.;
                        numberOfDataPoints = 0;
                        distanceZero = activity.laps[m].trackPoints[n].distanceMeters;
                        dtZero = activity.laps[m].trackPoints[n].time;
                        break;
                    }
                }
            }
        }
        bestSections.append(s);
    }

    QDateTime b = QDateTime::currentDateTime();
    qDebug() << "Statistics analysis took " << a.time().msecsTo(b.time()) << " ms.";

    return bestSections;
}

QVector<Training::Section> Training::readBestSections()
{
    // TODO
    QVector<Section> bestSections;
    return bestSections;
}

Training::Activity Training::readTcxFile(QString filename)
{
    activity = Activity{};
    pugi::xml_document doc;
    pugi::xml_parse_result trainingData = doc.load_file(filename.toUtf8().constData());

    if(trainingData.status != pugi::status_ok) { // Not possible to read file.
        activity.isValid = false;
        return activity;
    }

    pugi::xpath_query queryLaps("/TrainingCenterDatabase/Activities/Activity/Lap");
    pugi::xpath_query queryTrackpoints("./Track/Trackpoint");
    pugi::xpath_node_set laps = queryLaps.evaluate_node_set(doc);
    for(unsigned int i=0; i<laps.size(); i++ ) { // Loop over laps
        pugi::xml_node node = laps[i].node();
        Lap lap;
        lap.startTime           = QDateTime::fromString(QString(node.attribute("StartTime").value()).split(".")[0], "yyyy-MM-ddTHH:mm:ss");
        lap.totalTimeSeconds    = QString(node.child_value("TotalTimeSeconds")).toFloat();
        lap.distanceMeters      = QString(node.child_value("DistanceMeters")).toFloat();
        lap.maximumSpeed        = QString(node.child_value("MaximumSpeed")).toFloat();
        lap.calories            = QString(node.child_value("Calories")).toFloat();
        lap.averageHeartRateBpm = QString(node.child("AverageHeartRateBpm").child_value("Value")).toFloat();
        lap.maximumHeartRateBpm = QString(node.child("MaximumHeartRateBpm").child_value("Value")).toFloat();

        pugi::xpath_node_set trackpoints = queryTrackpoints.evaluate_node_set(node);
        for(unsigned int j=0; j<trackpoints.size(); j++) {
            pugi::xml_node subNode = trackpoints[j].node();
            TrackPoint tp;
            tp.time             = QDateTime::fromString(QString(subNode.child_value("Time")).split(".")[0], "yyyy-MM-ddTHH:mm:ss");
            tp.distanceMeters   = QString(subNode.child_value("DistanceMeters")).toFloat();
            tp.latitudeDegrees  = QString(subNode.child("Position").child_value("LatitudeDegrees")).toFloat();
            tp.longitudeDegrees = QString(subNode.child("Position").child_value("LongitudeDegrees")).toFloat();
            tp.heartRateBpm     = QString(subNode.child("HeartRateBpm").child_value("Value")).toFloat();
            tp.altitudeMeters   = QString(subNode.child_value("AltitudeMeters")).toFloat();
            tp.speed            = QString(subNode.child("Extensions").child("ns3:TPX").child_value("ns3:Speed")).toFloat();
            tp.runCadence       = QString(subNode.child("Extensions").child("ns3:TPX").child_value("ns3:RunCadence")).toFloat();
            lap.trackPoints.append(tp);
        }
        activity.laps.append(lap);
    }

    int numberOfLaps = activity.laps.size();

    if(numberOfLaps==0) {
        activity.isValid = false;
        return activity;
    }

    float heartRate = 0;
    for(int i=0; i<numberOfLaps; i++) {
        if(activity.laps[i].totalTimeSeconds != 0.)
            activity.laps[i].averageSpeed = activity.laps[i].distanceMeters / activity.laps[i].totalTimeSeconds;
        else
            activity.laps[i].averageSpeed = 0.;
        activity.distance += activity.laps[i].distanceMeters;
        activity.duration += activity.laps[i].totalTimeSeconds;
        heartRate += activity.laps[i].averageHeartRateBpm*activity.laps[i].totalTimeSeconds;
    }
    activity.speed = activity.distance / activity.duration;
    activity.dateTime = activity.laps[0].startTime;
    activity.heartRate = heartRate / activity.duration;
    activity.isValid = true;
    activity.id = id;

    int wrIndex = 0;
    for(int i=0; i<wrRunning.size(); i++) {
        if(wrRunning[i].distance >= activity.distance) {
            wrIndex = i;
            break;
        }
    }

    float wrDuration;
    if(wrIndex == 0) {
        wrDuration = activity.distance/wrRunning[wrIndex].distance*wrRunning[wrIndex].duration;
    }
    else {
        wrDuration = (wrRunning[wrIndex].duration - wrRunning[wrIndex-1].duration)*(activity.distance-wrRunning[wrIndex-1].distance)/(wrRunning[wrIndex].distance-wrRunning[wrIndex-1].distance) + wrRunning[wrIndex-1].duration;
    }
    activity.rating =  wrDuration / activity.duration * 100.;


    return activity;
}


void Training::defineWorldRecords()
{
    wrRunning = {
        WorldRecord(   100.,      9.58),
        WorldRecord(   200.,     19.19),
        WorldRecord(   400.,     43.03),
        WorldRecord(   800.,    100.91),
        WorldRecord(  1500.,    206.00),
        WorldRecord(  5000.,    757.35),
        WorldRecord( 10000.,   1577.53),
        WorldRecord( 42195.,   7299.00)
    };
}


Training::Activity Training::getActivity()
{
    return activity;
}
