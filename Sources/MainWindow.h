#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void on_newLeanerPushButton_clicked();

    void on_quitPushButton_clicked();

    void on_loginPushButton_clicked();

private:
    Ui::MainWindow *mUi;
};
//-----------------------------------------------------------------------------
#endif // MAINWINDOW_H
