#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "NewLearnerDialog.h"
#include "LoginDialog.h"
//-----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mUi(new Ui::MainWindow)
{
    mUi->setupUi(this);

    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(QPixmap(":/Images/English.png")));
    setPalette(palette);
}
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete mUi;
}
//-----------------------------------------------------------------------------
void MainWindow::on_newLeanerPushButton_clicked()
{
    NewLearnerDialog(this);
}
//-----------------------------------------------------------------------------
void MainWindow::on_quitPushButton_clicked()
{
    qApp->quit();
}
//-----------------------------------------------------------------------------
void MainWindow::on_loginPushButton_clicked()
{
    LoginDialog(this);
}
//-----------------------------------------------------------------------------
