#include "profiletile.h"

ProfileTile::ProfileTile()
{
    QFont fontTitle;
    fontTitle.setBold(true);
    fontTitle.setPointSize(12);

    QLabel *labelTitle = new QLabel(tr("Profile"), this);
    labelTitle->setFont(fontTitle);

    labelTitle->setGeometry(10,-10,320,50);
    int shift = 25;

    QString styleSheetName = QString("QLabel { color : gray; }");

    labelActivityText = new QLabel(this);
    //labelNumberOfTrainingsText = new QLabel(this);
    labelProfileNameText = new QLabel(this);
    labelActivity = new QLabel(this);
    //labelNumberOfTrainings = new QLabel(this);
    labelProfileName = new QLabel(this);
    labelFolderText = new QLabel(this);
    labelFolder = new QLabel(this);


    labelActivityText->setStyleSheet(styleSheetName);
    //labelNumberOfTrainingsText->setStyleSheet(styleSheetName);
    labelProfileNameText->setStyleSheet(styleSheetName);
    labelFolderText->setStyleSheet(styleSheetName);

    labelActivity = new QLabel(this);
    //labelNumberOfTrainings = new QLabel(this);
    labelProfileName = new QLabel(this);

    labelActivityText->setText(tr("Activity"));
    //labelNumberOfTrainingsText->setText(tr("Number Of Trainings"));
    labelProfileNameText->setText(tr("Profile Name"));
    labelFolderText->setText(tr("Folder"));

    labelProfileNameText->setGeometry(10,-10+shift,320,50);
    labelActivityText->setGeometry(150,-10+shift,400,50); // 35
    //labelNumberOfTrainingsText->setGeometry(110,80,400,50);
    labelFolderText->setGeometry(10,35+shift,400,50); // 80

    labelProfileName->setGeometry(10,7+shift,400,50);
    labelActivity->setGeometry(150,7+shift,400,50); // 52
    labelFolder->setGeometry(10,52+shift,400,50); // 97

    setFrameStyle(0);
    setMinimumSize(350, 130);
    setMaximumSize(350, 130);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //resize(200, 150);

    connect(MessageAgent::getInstance(), SIGNAL(profileChanged()), this, SLOT(updateProfile()));
    updateProfile();
}

void ProfileTile::updateProfile()
{
    UserSettings::profile p = UserSettings::getInstance()->getCurrentProfile();
    if(p.name != "") {
        labelProfileName->setText(p.name);
        labelActivity->setText(p.activity);
        labelFolder->setText(p.folder.absolutePath());
    }
    else {
        labelProfileName->setText(tr("-"));
        labelActivity->setText(tr("-"));
        labelFolder->setText(tr("-"));
    }
}
