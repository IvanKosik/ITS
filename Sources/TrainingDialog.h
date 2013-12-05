#ifndef TRAININGDIALOG_H
#define TRAININGDIALOG_H

#include "TrainingComplexityDialog.h"
#include "Phrase.h"

#include <QDialog>
#include <QRadioButton>
//-----------------------------------------------------------------------------
namespace Ui
{
    class TrainingDialog;
}
//-----------------------------------------------------------------------------
class TrainingDialog : public QDialog
{
    Q_OBJECT

public:
    static const QSize PronounceButtonSize;

    explicit TrainingDialog(TrainingComplexityDialog::Complexity complexity
                            , bool withTranslation, QWidget *parent = 0);
    ~TrainingDialog();

private:
    void askRandomPhrase();

    Ui::TrainingDialog *mUi;
    Phrases mPhrases;
    QList<QRadioButton *> mAnswerOptions;
    qint32 mTrueAnswerNumber;

private slots:
    void answerPushButtonClicked();
};
//-----------------------------------------------------------------------------
#endif // TRAININGDIALOG_H
