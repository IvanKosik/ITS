#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Db.h"

#include <QMainWindow>
//-----------------------------------------------------------------------------
namespace Ui
{
    class MainWindow;
}
//-----------------------------------------------------------------------------
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void sessionOpened(Id learnerId);
    void sessionClosed();

    void on_newLeanerPushButton_clicked();
    void on_logPushButton_clicked();
    void on_dictionaryPushButton_clicked();
    void on_quitPushButton_clicked();

private:
    Ui::MainWindow *mUi;
};
//-----------------------------------------------------------------------------
#endif // MAINWINDOW_H
