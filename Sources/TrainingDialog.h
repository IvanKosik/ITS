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
    static const qint32 ScoreIncrement;
    static const qint32 ScoreDecrement;

    explicit TrainingDialog(TrainingComplexityDialog::Complexity complexity
                            , bool withTranslation, QWidget *parent = 0);
    ~TrainingDialog();

private:
    void askRandomPhrase();

    Ui::TrainingDialog *mUi;
    TrainingComplexityDialog::Complexity mComplexity;
    bool mWithTranslation;
    Phrases mPhrases;
    QList<QRadioButton *> mAnswerOptions;
    qint32 mTrueAnswerNumber;
    qint32 mPhraseNumber;

private slots:
    void answerPushButtonClicked();
    void on_pronouncePushButton_clicked();
};
//-----------------------------------------------------------------------------
#endif // TRAININGDIALOG_H
