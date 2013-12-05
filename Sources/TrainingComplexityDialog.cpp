#include "TrainingComplexityDialog.h"
#include "ui_TrainingComplexityDialog.h"

#include <QPushButton>
//-----------------------------------------------------------------------------
TrainingComplexityDialog::TrainingComplexityDialog(QWidget *parent)
    : QDialog(parent)
    , mUi(new Ui::TrainingComplexityDialog)
{
    mUi->setupUi(this);


    // Buttons:
    QPixmap checkPixmap(":/Images/Check.png");
    QPushButton *okPushButton = new QPushButton(checkPixmap, tr("&OK")
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


    exec();
}
//-----------------------------------------------------------------------------
TrainingComplexityDialog::~TrainingComplexityDialog()
{
    delete mUi;
}
//-----------------------------------------------------------------------------
const TrainingComplexityDialog::Complexity TrainingComplexityDialog::getComplexity() const
{
    return mComplexity;
}
//-----------------------------------------------------------------------------
const bool TrainingComplexityDialog::needTranslation() const
{
    return mWithTranslation;
}
//-----------------------------------------------------------------------------
void TrainingComplexityDialog::okPushButtonClicked()
{
    mUi->easyRadioButton->isChecked() ? mComplexity = Easy
            : mUi->mediumRadioButton->isChecked() ? mComplexity = Medium
            : mComplexity = Hard;
    mWithTranslation = mUi->translationCheckBox->isChecked();
    done(QDialog::Accepted);
}
//-----------------------------------------------------------------------------
void TrainingComplexityDialog::on_hardRadioButton_toggled(bool checked)
{
    mUi->translationCheckBox->setEnabled(checked);
}
//-----------------------------------------------------------------------------
