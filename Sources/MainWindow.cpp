#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "NewLearnerDialog.h"
#include "LoginDialog.h"
#include "Session.h"
#include "Db.h"
//-----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mUi(new Ui::MainWindow)
{
    mUi->setupUi(this);

    //% http://stackoverflow.com/questions/5795214/qt-statusbar-color
    mUi->statusBar->setStyleSheet("QStatusBar{padding-left:8px;background:rgba(0,0,0,100);color:white;}");

    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(QPixmap(":/Images/English.png")));
    setPalette(palette);

    connect(Session::instance(), SIGNAL(opened(Id)), SLOT(sessionOpened(Id)));
    connect(Session::instance(), SIGNAL(closed()), SLOT(sessionClosed()));
}
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete mUi;
}
//-----------------------------------------------------------------------------
void MainWindow::sessionOpened(Id learnerId)
{
    mUi->logPushButton->setText("&Logout");
    Learner learner = Db::instance()->getLearner(learnerId);
    mUi->statusBar->showMessage("Logged learner: " + learner.getNickname());
}
//-----------------------------------------------------------------------------
void MainWindow::sessionClosed()
{
    mUi->logPushButton->setText("&Login");
    mUi->statusBar->clearMessage();
}
//-----------------------------------------------------------------------------
void MainWindow::on_newLeanerPushButton_clicked()
{
    NewLearnerDialog(this);
}
//-----------------------------------------------------------------------------
void MainWindow::on_logPushButton_clicked()
{
    if (Session::instance()->wasOpen()) {
        // Logout:
        Session::instance()->close();
    } else {
        // Login:
        LoginDialog(this);
    }
}
//-----------------------------------------------------------------------------
void MainWindow::on_quitPushButton_clicked()
{
    qApp->quit();
}
//-----------------------------------------------------------------------------
