#include "initconfiguration.h"

initconfiguration::initconfiguration()
{
    QFile file(initFilename);
    if(file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        userFolder = "";
        userFilename = "";
        while(!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(" ");
            if(fields[0] == "Ordner") {
                userFolder = fields[2];
            }
            if(fields[0] == "Datei") {
                userFilename = fields[2];
            }
        }
    }
    if (userFilename == "" || userFolder == "") {
        initializationOK = 0;
    }
    else {
        initializationOK = 1;
    }
}

bool initconfiguration::getInitValue() {
    return initializationOK;
}


void initconfiguration::setInitialization(QString folderInput, QString fileInput) {
    userFolder = folderInput;
    userFilename = fileInput;
    QFile file(initFilename);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        QString folderQ = "Ordner = " + userFolder + " # In diesem Ordner befindet sich die Benutzerdatei, die beim letzten Programmaufruf geladen war.";
        QString fileQ = "Datei = " + userFilename + " # Dies ist die Benutzerdatei, die beim letzten Programmaufruf geladen war.";
        stream << folderQ << endl;
        stream << fileQ << endl;
    }
}

QString initconfiguration::getUserFolder(){
    return userFolder;
}

QString initconfiguration::getUserFilename(){
    return userFilename;
}



const QString initconfiguration::initFilename = "parameter.init";
