#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    centralWidget = new CentralWidget;
    setCentralWidget(centralWidget);

    setWindowTitle(QString("Athlet"));
    resize(1200,900);

    setupMenu();

    SqlHelper* h = SqlHelper::getInstance();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupMenu()
{
    userSettings = UserSettings::getInstance();
    connect(userSettings, SIGNAL(profileChanged(UserSettings::profile)), centralWidget, SLOT(onProfileChanged(UserSettings::profile)));
    dialogNew = new UserDialog("NEW", userSettings);
    dialogChoose = new UserDialog("CHOOSE", userSettings);
    dialogEdit = new UserDialog("EDIT", userSettings);
    dialogDelete = new UserDialog("DELETE", userSettings);

    menuProfile = new QMenu();

    menuProfile = menuBar()->addMenu(tr("&Profile"));
    menuProfile->addAction(tr("&New"), dialogNew, SLOT(showDialog()));
    menuProfile->addAction(tr("&Choose"), dialogChoose, SLOT(showDialog()));
    menuProfile->addAction(tr("&Edit"), dialogEdit, SLOT(showDialog()));
    menuProfile->addAction(tr("&Delete"), dialogDelete, SLOT(showDialog()));
}
