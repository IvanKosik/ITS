#include "NewLearnerDialog.h"
#include "ui_NewLearnerDialog.h"

#include "Db.h"
#include "Learner.h"

#include <QtWidgets>
//-----------------------------------------------------------------------------
NewLearnerDialog::NewLearnerDialog(QWidget *parent)
    : QDialog(parent)
    , mUi(new Ui::NewLearnerDialog)
{
    mUi->setupUi(this);


    // Buttons:
    QPixmap checkPixmap(":/Images/Check.png");
    okPushButton = new QPushButton(checkPixmap, tr("&OK")
                                   , mUi->dialogButtonBox);
    okPushButton->setIconSize(checkPixmap.size());
    connect(okPushButton, SIGNAL(clicked()), SLOT(okPushButtonClicked()));

    QPixmap crossPixmap(":/Images/Cross.png");
    QPushButton *cancelPushButton = new QPushButton(crossPixmap, tr("&Cancel")
                                                    , mUi->dialogButtonBox);
    cancelPushButton->setIconSize(crossPixmap.size());
    connect(cancelPushButton, SIGNAL(clicked()), SLOT(close()));

    mUi->dialogButtonBox->addButton(okPushButton, QDialogButtonBox::AcceptRole);
    mUi->dialogButtonBox->addButton(cancelPushButton, QDialogButtonBox::RejectRole);


    on_nicknameLineEdit_textChanged(mUi->nicknameLineEdit->text());
    on_passwordLineEdit_textChanged(mUi->passwordLineEdit->text());
    on_repeatPasswordLineEdit_textChanged(mUi->repeatPasswordLineEdit->text());


    exec();
}
//-----------------------------------------------------------------------------
NewLearnerDialog::~NewLearnerDialog()
{
    delete mUi;
}
//-----------------------------------------------------------------------------
void NewLearnerDialog::changeAvatar(const QString &fileName)
{
    QPixmap avatarPixmap;
    avatarPixmap.load(fileName);
    if ((avatarPixmap.size().width() > AvatarSize.width())
            || (avatarPixmap.size().height() > AvatarSize.height())) {
        avatarPixmap = avatarPixmap.scaled(AvatarSize, Qt::KeepAspectRatio,
                                           Qt::SmoothTransformation);
    }

    mUi->avatarLabel->resize(avatarPixmap.size());
    mUi->avatarLabel->setPixmap(avatarPixmap);
}
//-----------------------------------------------------------------------------
void NewLearnerDialog::showDataCheckResult(QLabel *dataCheckResultLabel,
				   bool dataCheckResult, QString toolTip)
{
    QPixmap dataCheckResultPixmap;
    if (dataCheckResult) {
        dataCheckResultPixmap.load(":/Images/Check.png");
    } else {
        dataCheckResultPixmap.load(":/Images/Cross.png");
    }

    dataCheckResultLabel->resize(dataCheckResultPixmap.size());
    dataCheckResultLabel->setPixmap(dataCheckResultPixmap);

    dataCheckResultLabel->setToolTip(toolTip);
}
//-----------------------------------------------------------------------------
void NewLearnerDialog::comparePasswords(QString password, QString repeatPassword)
{
    if (password == repeatPassword) {
        showDataCheckResult(mUi->repeatPasswordCheckLabel, true, tr("OK"));
        isRepeatPasswordCorrect = true;
    }
    else {
        showDataCheckResult(mUi->repeatPasswordCheckLabel, false,
                tr("Passwords don't match!"));
        isRepeatPasswordCorrect = false;
    }

    checkData();
}
//-----------------------------------------------------------------------------
void NewLearnerDialog::checkData()
{
    if (isNicknameCorrect && isRepeatPasswordCorrect) {
        okPushButton->setEnabled(true);
    }
    else {
        okPushButton->setDisabled(true);
    }
}
//-----------------------------------------------------------------------------
void NewLearnerDialog::okPushButtonClicked()
{
    // "OK" button will be disabled if DB already contains learner
    // with indicated name.
    Gender::Type genderType;
    mUi->indeterminateRadioButton->isChecked() ? genderType = Gender::Indeterminate
            : mUi->maleRadioButton->isChecked() ? genderType = Gender::Male
            : genderType = Gender::Female;
    Db::instance()->addLearner(Learner(mUi->nicknameLineEdit->text()
                                       , mUi->passwordLineEdit->text()
                                       , mUi->descriptionTextEdit->toPlainText()
                                       , genderType
                                       , *mUi->avatarLabel->pixmap()));
    done(QDialog::Accepted);
}
//-----------------------------------------------------------------------------
void NewLearnerDialog::on_nicknameLineEdit_textChanged(QString nickname)
{
    if (!nickname.isEmpty()) {
        if (!Db::instance()->hasLearner(Learner(nickname))) {
            showDataCheckResult(mUi->nicknameCheckLabel, true, tr("OK"));
            isNicknameCorrect = true;
        }
        else {
            showDataCheckResult(mUi->nicknameCheckLabel, false,
                    tr("The database already contains such learner!"));
            isNicknameCorrect = false;
        }
    } else {
        showDataCheckResult(mUi->nicknameCheckLabel, false, tr("Enter a nickname!"));
        isNicknameCorrect = false;
    }

    checkData();
}
//-----------------------------------------------------------------------------
void NewLearnerDialog::on_passwordLineEdit_textChanged(QString password)
{
    //% if (пароль надежный) {
    showDataCheckResult(mUi->passwordCheckLabel, true, tr("OK"));
    comparePasswords(password, mUi->repeatPasswordLineEdit->text());
}
//-----------------------------------------------------------------------------
void NewLearnerDialog::on_repeatPasswordLineEdit_textChanged(QString repeatedPassword)
{
    comparePasswords(mUi->passwordLineEdit->text(), repeatedPassword);
}
//-----------------------------------------------------------------------------
void NewLearnerDialog::on_changeAvatarPushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Change Avatar"),
						    QString(),
                            tr("Images (*.png *.jpg)"));
    if (!fileName.isEmpty()) {
        changeAvatar(fileName);
    }
}
//-----------------------------------------------------------------------------
