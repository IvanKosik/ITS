#include "TrainingDialog.h"
#include "ui_TrainingDialog.h"

#include "Db.h"
#include "Speaker.h"
#include "Session.h"
#include "TrainingComplexityDialog.h"

#include <QMessageBox>

#include <algorithm>

#include <QDebug>

const QSize TrainingDialog::PronounceButtonSize = QSize(128, 128);
const qint32 TrainingDialog::ScoreIncrement = 10;
const qint32 TrainingDialog::ScoreDecrement = -10;
//-----------------------------------------------------------------------------
TrainingDialog::TrainingDialog(TrainingComplexityDialog::Complexity complexity
                               , bool withTranslation, QWidget *parent)
    : QDialog(parent)
    , mUi(new Ui::TrainingDialog)
    , mComplexity(complexity)
    , mWithTranslation(withTranslation)
{
    mUi->setupUi(this);


    mAnswerOptions.append(mUi->aRadioButton);
    mAnswerOptions.append(mUi->bRadioButton);
    mAnswerOptions.append(mUi->cRadioButton);
    mAnswerOptions.append(mUi->dRadioButton);


    switch (mComplexity) {
    case TrainingComplexityDialog::Easy:
        mUi->lettersLabel->hide();
        mUi->answerLineEdit->hide();
        break;
    case TrainingComplexityDialog::Medium:
        mUi->answerOptionsGroupBox->hide();
        break;
    case TrainingComplexityDialog::Hard:
        mUi->answerOptionsGroupBox->hide();
        mUi->lettersLabel->hide();
        break;
    }


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

    //%qDebug() << "size:" << mPhrases.size();//%

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
    // Generate number of phrase:
    mPhraseNumber = ((qreal)qrand() / RAND_MAX) * (mPhrases.size() - 1);
    QString phrase = mPhrases.at(mPhraseNumber).getEng();
    // Pronounce english phrase:
    Speaker::instance()->pronounce(phrase);
    qDebug() << "Question phrase:" << phrase;

    QString letters;

    switch (mComplexity) {
    case TrainingComplexityDialog::Easy:
        // Generate number of radioButton with correct answer.
        mTrueAnswerNumber = ((qreal)qrand() / RAND_MAX) * (mAnswerOptions.size() - 1);

        // Display answers:
        for (qint32 i = 0; i < mAnswerOptions.size(); ++i) {
            // If it's number of the radioButton with correct answer:
            if (i == mTrueAnswerNumber) {
                mAnswerOptions.at(i)->setText("&" + QString::number(i + 1) + ") " + phrase);
            } else {
                // Generate numbers of wrong phrases:
                qint32 wrongPhraseNumber = ((qreal)qrand() / RAND_MAX) * (mPhrases.size() - 1);
                // Generate new numbers, if wrong phrase number coincided with number of correct phrase:
                while (wrongPhraseNumber == mPhraseNumber) {
                    wrongPhraseNumber = ((qreal)qrand() / RAND_MAX) * (mPhrases.size() - 1);
                }
                mAnswerOptions.at(i)->setText("&" + QString::number(i + 1)
                                              + ") " + mPhrases.at(wrongPhraseNumber).getEng());
            }
        }
        break;
    case TrainingComplexityDialog::Medium:
        letters = phrase;
        std::random_shuffle(letters.begin(), letters.end());
        mUi->lettersLabel->setText("Letters: " + letters);
        break;
    case TrainingComplexityDialog::Hard:
        break;
    }
}
//-----------------------------------------------------------------------------
void TrainingDialog::answerPushButtonClicked()
{
    Id learnerId = Session::instance()->getLearnerId();
    Learner learner = Db::instance()->getLearner(learnerId);
    qint32 newScore;
    bool isCorrectAnswer = false;
    QString correctAnswer = "";
    QString phrase = mPhrases.at(mPhraseNumber).getEng();
    QString rusPhrase = mPhrases.at(mPhraseNumber).getRus();

    switch (mComplexity) {
    case TrainingComplexityDialog::Easy:
        // Get number of chosen answer:
        qint32 chosenAnswerNumber;
        for (qint32 i = 0; i < mAnswerOptions.size(); ++i) {
            if (mAnswerOptions.at(i)->isChecked()) {
                chosenAnswerNumber = i;
                break;
            }
        }
        // If it's correct answer:
        if (chosenAnswerNumber == mTrueAnswerNumber) {
            isCorrectAnswer = true;
        }
        correctAnswer = mAnswerOptions.at(mTrueAnswerNumber)->text().remove(0, 1);
        break;
    case TrainingComplexityDialog::Medium:
        correctAnswer = phrase;
        if (mUi->answerLineEdit->text() == correctAnswer) {
            isCorrectAnswer = true;
        }
        break;
    case TrainingComplexityDialog::Hard:
        if (mWithTranslation) {
            correctAnswer = rusPhrase;
            if (mUi->answerLineEdit->text() == correctAnswer) {
                isCorrectAnswer = true;
            }

        } else {
            correctAnswer = phrase;
            if (mUi->answerLineEdit->text() == correctAnswer) {
                isCorrectAnswer = true;
            }
        }
        break;
    }

    if (isCorrectAnswer) {
        // Score:
        // Easy: 10 * 1; Medium: 10 * 2; Hard: 10 * 3;
        qDebug() << "getScore:" << learner.getScore();
        newScore = learner.getScore() + ScoreIncrement * (mComplexity + 1);
        QMessageBox::information(this, "Correct Answer"
                                 , "Your answer is correct. Your score is "
                                 + QString::number(newScore));
    }
    else {
        newScore = learner.getScore() + ScoreDecrement * (mComplexity + 1);
        QMessageBox::information(this, "Wrong Answer", "Your answer is wrong. Your score is: "
                                 + QString::number(newScore) + "\nCorrect answer was: "
                                 + correctAnswer);
    }

    Db::instance()->updateLearnerScore(learnerId, newScore);

    askRandomPhrase();
}
//-----------------------------------------------------------------------------
void TrainingDialog::on_pronouncePushButton_clicked()
{
    Speaker::instance()->pronounce(mPhrases.at(mPhraseNumber).getEng());
}
//-----------------------------------------------------------------------------
