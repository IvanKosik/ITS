#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
//-----------------------------------------------------------------------------
namespace Ui
{
    class LoginDialog;
}
//-----------------------------------------------------------------------------
class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private:
    Ui::LoginDialog *mUi;
    QSqlTableModel *mLearnerModel;

private slots:
    void okPushButtonClicked();
};
//-----------------------------------------------------------------------------
#endif // LOGINDIALOG_H
