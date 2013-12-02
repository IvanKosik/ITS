#ifndef NEWLEARNER_H
#define NEWLEARNER_H

#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

const QSize AvatarSize = QSize(64, 64); //- это должно быть в .h файле? //- Поместить в наиболее подходящее место (область видимости) (можно сделать static const внутри класса).
//-----------------------------------------------------------------------------
namespace Ui
{
    class NewLearnerDialog;
}
//-----------------------------------------------------------------------------
class NewLearnerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewLearnerDialog(QWidget *parent = 0);
    ~NewLearnerDialog();

private:
    Ui::NewLearnerDialog *mUi;

    void changeAvatar(const QString &fileName);
    void showDataCheckResult(QLabel *dataCheckResultLabel, bool dataCheckResult,
			     QString toolTip);
    void comparePasswords(QString password, QString repeatPassword);
    void checkData();

    QPushButton *okPushButton;

    bool isNicknameCorrect;
    bool isRepeatPasswordCorrect;

private slots:   
    void okPushButtonClicked();

    void on_nicknameLineEdit_textChanged(QString nickname);
    void on_passwordLineEdit_textChanged(QString password);
    void on_repeatPasswordLineEdit_textChanged(QString repeatedPassword);
    void on_changeAvatarPushButton_clicked();
};
//-----------------------------------------------------------------------------
#endif // NEWLEARNER_H
