#include "userdialog.h"

UserDialog::UserDialog()
{
    QDialog *subDialog = new QDialog;
    subDialog->setWindowTitle("Sub Dialog");
    QPushButton *button = new QPushButton("Push to open new dialog", this);
    connect(button, SIGNAL(clicked()), this, SLOT(onButtonCancelClicked()));
}

UserDialog::UserDialog(QString mode, UserSettings *userSettings)
{
    this->userSettings = userSettings;

    comboBoxProfiles = new QComboBox();
    lineEditProfile = new QLineEdit();
    lineEditFolder = new QLineEdit();
    lineEditActivity = new QLineEdit();

    buttonNew = new QPushButton();
    buttonNew->setText(tr("Create"));
    buttonNew->setToolTip(tr("Create a new profile."));

    buttonSubmit = new QPushButton();
    buttonSubmit->setText(tr("Submit"));
    buttonSubmit->setToolTip(tr("Choose the selected profile."));

    buttonChoose = new QPushButton();
    buttonChoose->setText(tr("Choose"));
    buttonChoose->setToolTip(tr("Choose the selected profile."));

    buttonDelete = new QPushButton();
    buttonDelete->setText(tr("Delete"));
    buttonDelete->setToolTip(tr("Delete the selected profile."));

    buttonEdit = new QPushButton();
    buttonEdit->setText(tr("Edit"));
    buttonEdit->setToolTip(tr("Edit the selected profile."));

    buttonCancel = new QPushButton();
    buttonCancel->setText(tr("Cancel"));
    buttonCancel->setToolTip(tr("Exit this screen without choosing a profile."));

    comboBoxActivities = new QComboBox();
    QVector<QString> possibleActivities = userSettings->getPossibleActivities();
    for(int i=0; i<possibleActivities.size(); i++)
        comboBoxActivities->addItem(possibleActivities[i]);

    // Connect signals with slot.
    connect(buttonNew, SIGNAL(clicked()), this, SLOT(onButtonNewClicked()));
    connect(buttonCancel, SIGNAL(clicked()), this, SLOT(onButtonCancelClicked()));
    connect(comboBoxProfiles, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxChanged(int)));
    connect(buttonChoose, SIGNAL(clicked()), this, SLOT(onButtonChooseClicked()));
    connect(buttonEdit, SIGNAL(clicked()), this, SLOT(onButtonEditClicked()));
    connect(buttonDelete, SIGNAL(clicked()), this, SLOT(onButtonDeleteClicked()));

    layoutForm = new QFormLayout();
    layoutButtons = new QHBoxLayout();
    layoutDialog = new QVBoxLayout();

    if(mode == "NEW")
        createDialogNew();
    else if(mode == "CHOOSE")
        createDialogChoose();
    else if(mode == "EDIT")
        createDialogEdit();
    else if(mode == "DELETE")
        createDialogDelete();
    else
        qDebug() << "UserDialog: No such dialog mode.";

    message = new QLabel();
    message->setStyleSheet("QLabel { color : red; }");

    layoutDialog->addLayout(layoutForm);
    layoutDialog->addWidget(message);
    layoutDialog->addLayout(layoutButtons);

    this->setLayout(layoutDialog);

    this->setFixedSize(400,180);
}


void UserDialog::showDialog()
{
    message->setText("");

    if(mode == "NEW") {
        lineEditProfile->clear();
        lineEditFolder->clear();
        comboBoxActivities->setCurrentIndex(0);
    }
    else {
        QVector<QString> profileNames = userSettings->getProfileNames();
        if(profileNames.size() == 0) {
            QMessageBox messageBox;
            messageBox.critical(0,tr("Error"),tr("You have not created a profile yet. Please create a profile first."));
            messageBox.setFixedSize(500,200);
            return;
        }
        comboBoxProfiles->clear();
        for(int i=0; i<profileNames.size(); i++) {
            comboBoxProfiles->addItem(profileNames[i]);
        }
        if(profileNames.size() != 0) {
            comboBoxProfiles->setCurrentIndex(userSettings->indexOfProfile);
            lineEditFolder->setText(userSettings->getFolder(userSettings->indexOfProfile));
        }
        comboBoxActivities->setCurrentIndex(userSettings->getActivityIndex(userSettings->getActivity(userSettings->indexOfProfile)));
    }
    show();
}


void UserDialog::onButtonNewClicked()
{
    bool isValidProfile = userSettings->addProfile(lineEditProfile->text(), lineEditFolder->text(), comboBoxActivities->currentText(), message);
    if(isValidProfile)
        this->close();
}

void UserDialog::onButtonSubmitClicked()
{

}

void UserDialog::onButtonEditClicked()
{
    UserSettings::profile p;
    p.name = comboBoxProfiles->currentText();
    p.folder = QDir(lineEditFolder->text());
    p.activity = comboBoxActivities->currentText();
    bool isValid = userSettings->editProfile(comboBoxProfiles->currentIndex(), p, message);
    if(isValid)
        close();
}

void UserDialog::onButtonDeleteClicked()
{
    userSettings->deleteProfile(comboBoxProfiles->currentIndex());
    close();
}

void UserDialog::onButtonCancelClicked()
{
    close();
}

void UserDialog::onComboBoxChanged(int index)
{
    if (comboBoxProfiles->count() == 0)
        return;
    lineEditFolder->setText(userSettings->getFolder(index));
    comboBoxActivities->setCurrentText(userSettings->getActivity(index));
}

void UserDialog::onButtonChooseClicked()
{
    userSettings->chooseProfile(comboBoxProfiles->currentIndex());
    close();
}

void UserDialog::createDialogNew()
{
    mode = "NEW";
    layoutForm->addRow(tr("&Profile:"), lineEditProfile);
    layoutForm->addRow(tr("&Folder:"), lineEditFolder);
    layoutForm->addRow(tr("&Activity:"), comboBoxActivities);

    layoutButtons->addStretch();
    layoutButtons->addWidget(buttonNew);
    layoutButtons->addWidget(buttonCancel);
}

void UserDialog::createDialogChoose()
{
    mode = "CHOOSE";
    layoutForm->addRow(tr("&Profile:"), comboBoxProfiles);
    layoutForm->addRow(tr("&Folder:"), lineEditFolder);
    layoutForm->addRow(tr("&Activity:"), comboBoxActivities);

    lineEditFolder->setEnabled(false);
    comboBoxActivities->setEnabled(false);

    layoutButtons->addStretch();
    layoutButtons->addWidget(buttonChoose);
    layoutButtons->addWidget(buttonCancel);
}

void UserDialog::createDialogEdit()
{
    mode = "EDIT";
    layoutForm->addRow(tr("&Profile:"), comboBoxProfiles);
    layoutForm->addRow(tr("&Folder:"), lineEditFolder);
    layoutForm->addRow(tr("&Activity:"), comboBoxActivities);

    layoutButtons->addStretch();
    layoutButtons->addWidget(buttonEdit);
    layoutButtons->addWidget(buttonCancel);
}

void UserDialog::createDialogDelete()
{
    mode = "DELETE";
    layoutForm->addRow(tr("&Profile:"), comboBoxProfiles);
    layoutForm->addRow(tr("&Folder:"), lineEditFolder);
    layoutForm->addRow(tr("&Activity:"), comboBoxActivities);

    lineEditFolder->setEnabled(false);
    comboBoxActivities->setEnabled(false);

    layoutButtons->addStretch();
    layoutButtons->addWidget(buttonDelete);
    layoutButtons->addWidget(buttonCancel);
}
