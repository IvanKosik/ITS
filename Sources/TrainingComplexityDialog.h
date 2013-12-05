#ifndef TRAININGCOMPLEXITYDIALOG_H
#define TRAININGCOMPLEXITYDIALOG_H

#include <QDialog>
//-----------------------------------------------------------------------------
namespace Ui
{
    class TrainingComplexityDialog;
}
//-----------------------------------------------------------------------------
class TrainingComplexityDialog : public QDialog
{
    Q_OBJECT

public:
    enum Complexity
    {
        Easy
        , Medium
        , Hard
    };

    explicit TrainingComplexityDialog(QWidget *parent = 0);
    ~TrainingComplexityDialog();

    const Complexity getComplexity() const;
    const bool needTranslation() const;

private:
    Ui::TrainingComplexityDialog *mUi;
    Complexity mComplexity;
    bool mWithTranslation;

private slots:
    void okPushButtonClicked();
    void on_hardRadioButton_toggled(bool checked);
};
//-----------------------------------------------------------------------------
#endif // TRAININGCOMPLEXITYDIALOG_H
