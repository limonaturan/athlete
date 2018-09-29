#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "centralwidget.h"
#include "usersettings.h"
#include "userdialog.h"
#include <QMenu>
#include "sqlhelper.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CentralWidget *centralWidget;
    UserSettings *userSettings;
    UserDialog *dialogNew;
    UserDialog *dialogChoose;
    UserDialog *dialogEdit;
    UserDialog *dialogDelete;
    QMenu *menuProfile;

    void setupMenu();

};

#endif // MAINWINDOW_H
