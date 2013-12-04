#include "AddPhraseDialog.h"
#include "ui_AddPhraseDialog.h"

#include "Phrase.h"
#include "Db.h"

#include <QPushButton>
#include <QFileDialog>
//-----------------------------------------------------------------------------
AddPhraseDialog::AddPhraseDialog(QWidget *parent)
    : QDialog(parent)
    , mUi(new Ui::AddPhraseDialog)
{
    mUi->setupUi(this);


    // Buttons:
    QPixmap checkPixmap(":/Images/Check.png");
    mOkPushButton = new QPushButton(checkPixmap, tr("&OK")
                                   , mUi->dialogButtonBox);
    mOkPushButton->setIconSize(checkPixmap.size());
    connect(mOkPushButton, SIGNAL(clicked()), SLOT(okPushButtonClicked()));

    QPixmap crossPixmap(":/Images/Cross.png");
    QPushButton *cancelPushButton = new QPushButton(crossPixmap, tr("&Cancel")
                                                    , mUi->dialogButtonBox);
    cancelPushButton->setIconSize(crossPixmap.size());
    connect(cancelPushButton, SIGNAL(clicked()), SLOT(close()));

    mUi->dialogButtonBox->addButton(mOkPushButton, QDialogButtonBox::AcceptRole);
    mUi->dialogButtonBox->addButton(cancelPushButton, QDialogButtonBox::RejectRole);


    checkInput();


    exec();
}
//-----------------------------------------------------------------------------
AddPhraseDialog::~AddPhraseDialog()
{
    delete mUi;
}
//-----------------------------------------------------------------------------
void AddPhraseDialog::checkInput()
{
    bool correctInput = true;
    if (mUi->englishPhraseLineEdit->text().isEmpty()
            || mUi->russianPhraseLineEdit->text().isEmpty()) {
        correctInput = false;
    }

    mOkPushButton->setEnabled(correctInput);
}
//-----------------------------------------------------------------------------
void AddPhraseDialog::changeImage(const QString &fileName)
{
    QPixmap image;
    image.load(fileName);
    if ((image.size().width() > Phrase::ImageSize.width())
            || (image.size().height() > Phrase::ImageSize.height())) {
        image = image.scaled(Phrase::ImageSize, Qt::KeepAspectRatio,
                             Qt::SmoothTransformation);
    }

    mUi->imageLabel->resize(image.size());
    mUi->imageLabel->setPixmap(image);
}
//-----------------------------------------------------------------------------
void AddPhraseDialog::okPushButtonClicked()
{
    Db::instance()->addPhrase(Phrase(mUi->englishPhraseLineEdit->text()
                                     , mUi->russianPhraseLineEdit->text()
                                     , *mUi->imageLabel->pixmap()));
    done(QDialog::Accepted);
}
//-----------------------------------------------------------------------------
void AddPhraseDialog::on_englishPhraseLineEdit_textChanged(const QString &)
{
    checkInput();
}
//-----------------------------------------------------------------------------
void AddPhraseDialog::on_russianPhraseLineEdit_textChanged(const QString &)
{
    checkInput();
}
//-----------------------------------------------------------------------------
void AddPhraseDialog::on_loadImagePushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load Image"),
                            QString(),
                            tr("Images (*.png *.jpg)"));
    if (!fileName.isEmpty()) {
        changeImage(fileName);
    }
}
//-----------------------------------------------------------------------------
