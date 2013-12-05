#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "NewLearnerDialog.h"
#include "LoginDialog.h"
#include "DictionaryDialog.h"
#include "TrainingComplexityDialog.h"
#include "TrainingDialog.h"
#include "Session.h"
#include "Db.h"

#include <QMessageBox>
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
void MainWindow::on_dictionaryPushButton_clicked()
{
    DictionaryDialog(this);
}
//-----------------------------------------------------------------------------
void MainWindow::on_trainingPushButton_clicked()
{
    /*
    NewGameDialog *newGamerDialog = new NewGameDialog(this);
        if (newGamerDialog->exec() == QDialog::Accepted) {
            NewGameDialog::Complexity complexity = newGamerDialog->getComplexity();
            Game *game = new Game(complexity, mDictionary, this);
            game->exec();
        }
        */
    Phrases phrases = Db::instance()->getPhrases();
    if (phrases.size() < 4) {
        QMessageBox::warning(this, tr("Expand Dictionary")
                             , tr("Expand the dictionary size. Min size is 4 phrases."));
        return;
    }

    TrainingComplexityDialog trainingComplexityDialog(this);
    if (trainingComplexityDialog.result() == QDialog::Accepted) {
        TrainingComplexityDialog::Complexity complexity = trainingComplexityDialog.getComplexity();
        bool withTranslation = trainingComplexityDialog.needTranslation();
        TrainingDialog(complexity, withTranslation, this);
    }
}
//-----------------------------------------------------------------------------
