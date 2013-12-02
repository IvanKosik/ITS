#include "MainWindow.h"
#include "Db.h"

#include <QApplication>
#include <QMessageBox>
#include <QTime>
//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    if (Db::instance()->getStatus() != Db::Ok) {
        QMessageBox::critical(0, "Error", "Cannot create DB connection!");
        return 1;
    }

    qsrand(QTime::currentTime().msec());

    MainWindow mainWindow;
    mainWindow.show();

    return application.exec();
}
//-----------------------------------------------------------------------------
