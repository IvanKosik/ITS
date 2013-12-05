#include "TrainingDialog.h"
#include "ui_TrainingDialog.h"

#include "Db.h"
#include "Speaker.h"

#include <QDebug>

const QSize TrainingDialog::PronounceButtonSize = QSize(128, 128);
//-----------------------------------------------------------------------------
TrainingDialog::TrainingDialog(TrainingComplexityDialog::Complexity complexity
                               , bool withTranslation, QWidget *parent)
    : QDialog(parent)
    , mUi(new Ui::TrainingDialog)
{
    mUi->setupUi(this);


    mAnswerOptions.append(mUi->aRadioButton);
    mAnswerOptions.append(mUi->bRadioButton);
    mAnswerOptions.append(mUi->cRadioButton);
    mAnswerOptions.append(mUi->dRadioButton);


    // Buttons:
    mUi->pronouncePushButton->setIconSize(PronounceButtonSize);

    QPixmap checkPixmap(":/Images/Check.png");
    QPushButton *answerPushButton = new QPushButton(checkPixmap, tr("Ans&wer")
                                   , mUi->dialogButtonBox);
    answerPushButton->setIconSize(checkPixmap.size());
    connect(answerPushButton, SIGNAL(clicked()), SLOT(answerPushButtonClicked()));

    QPixmap crossPixmap(":/Images/Cross.png");
    QPushButton *finishTrainingPushButton
            = new QPushButton(crossPixmap, tr("&Finish Training"), mUi->dialogButtonBox);
    finishTrainingPushButton->setIconSize(crossPixmap.size());
    connect(finishTrainingPushButton, SIGNAL(clicked()), SLOT(close()));

    mUi->dialogButtonBox->addButton(answerPushButton, QDialogButtonBox::AcceptRole);
    mUi->dialogButtonBox->addButton(finishTrainingPushButton, QDialogButtonBox::RejectRole);


    // Load all phrases from DB, which we can edit in the Dictionary dialog.
    mPhrases = Db::instance()->getPhrases();
    askRandomPhrase();

    qDebug() << "size:" << mPhrases.size();//%

    /*foreach (Phrase phrase, phrases) {  //%
        std::cout << "Phrase:" << phrase;
    }*/


    exec();
}
//-----------------------------------------------------------------------------
TrainingDialog::~TrainingDialog()
{
    delete mUi;
}
//-----------------------------------------------------------------------------
void TrainingDialog::askRandomPhrase()
{
    // Generate number of radioButton with correct answer.
    mTrueAnswerNumber = ((qreal)qrand() / RAND_MAX) * (mAnswerOptions.size() - 1);

    // Generate number of phrase:
    qint32 phraseNumber = ((qreal)qrand() / RAND_MAX) * (mPhrases.size() - 1);

    // Pronounce english phrase:
    Speaker::instance()->pronounce(mPhrases.at(phraseNumber).getEng());
    qDebug() << "Question phrase:" << mPhrases.at(phraseNumber).getEng();

    // Display answers:
    for (qint32 i = 0; i < mAnswerOptions.size(); ++i) {
        // If it's number of the radioButton with correct answer:
        if (i == mTrueAnswerNumber) {
            mAnswerOptions.at(i)->setText(mPhrases.at(phraseNumber).getEng());
        } else {
            // Generate numbers of wrong phrases:
            qint32 wrongPhraseNumber = ((qreal)qrand() / RAND_MAX) * (mPhrases.size() - 1);
            // Generate new numbers, if wrong phrase number coincided with number of correct phrase:
            while (wrongPhraseNumber == phraseNumber) {
                wrongPhraseNumber = ((qreal)qrand() / RAND_MAX) * (mPhrases.size() - 1);
            }
            mAnswerOptions.at(i)->setText(mPhrases.at(wrongPhraseNumber).getEng());
        }
    }
}
//-----------------------------------------------------------------------------
void TrainingDialog::answerPushButtonClicked()
{
    // Get number of chosen answer:
    qint32 chosenAnswerNumber;
    for (qint32 i = 0; i < mAnswerOptions->size(); ++i) {
        if (mAnswerOptions.at(i)->isChecked()) {
            chosenAnswerNumber = i;
            break;
        }
    }

    // If it's correct answer:
    if (chosenAnswerNumber == mTrueAnswerNumber) {
        generateQuestion();
        mScore += 1 + mScoreBonus;
        ++mScoreBonus;

        ui->scoreLabel->setText("Score: " + QString::number(mScore));
    }
    else {
        QMessageBox::information(this, "Wrong Answer", "Your answer is wrong. Your score: " + QString::number(mScore)); //- Add score info.
        close();
    }

    if (mTrueAnswerNumber == )
}
//-----------------------------------------------------------------------------
