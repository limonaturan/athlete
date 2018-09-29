#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLayoutItem>
#include <QObject>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>

#include "usersettings.h"


class UserDialog : public QDialog
{
    Q_OBJECT
public:
    UserDialog();
    UserDialog(UserSettings* userSettings);
    UserDialog(QString mode, UserSettings* userSettings);

signals:
    void profileChanged();

public slots:
    void showDialog();

private slots:
    void onButtonNewClicked();
    void onButtonSubmitClicked();
    void onButtonEditClicked();
    void onButtonDeleteClicked();
    void onButtonCancelClicked();
    void onComboBoxChanged(int);
    void onButtonChooseClicked();

private:
    void createDialogNew();
    void createDialogChoose();
    void createDialogEdit();
    void createDialogDelete();

    QLineEdit *lineEditProfile;
    QLineEdit *lineEditFolder;
    QLineEdit *lineEditActivity;

    QComboBox *comboBoxProfiles;
    QComboBox *comboBoxActivities;

    QFormLayout *layoutForm;
    QHBoxLayout *layoutButtons;
    QVBoxLayout *layoutDialog;

    QLabel *message;

    QPushButton *buttonSubmit;
    QPushButton *buttonCancel;
    QPushButton *buttonDelete;
    QPushButton *buttonChoose;
    QPushButton *buttonEdit;
    QPushButton *buttonNew;

    UserSettings *userSettings;

    QString mode;

};

#endif // USERDIALOG_H
