#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QDataWidgetMapper>
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
    QSqlQueryModel *mLearnerModel;
    QDataWidgetMapper *mDataWidgetMapper;

private slots:
    void okPushButtonClicked();
    void currentLearnerChanged(const QModelIndex &current
                               , const QModelIndex &);

//    void on_learnerTableView_activated(const QModelIndex &index);
};
//-----------------------------------------------------------------------------
#endif // LOGINDIALOG_H
