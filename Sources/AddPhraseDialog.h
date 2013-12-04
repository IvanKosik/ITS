#ifndef ADDPHRASEDIALOG_H
#define ADDPHRASEDIALOG_H

#include <QDialog>
//-----------------------------------------------------------------------------
namespace Ui
{
    class AddPhraseDialog;
}
//-----------------------------------------------------------------------------
class AddPhraseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPhraseDialog(QWidget *parent = 0);
    ~AddPhraseDialog();

private:
    void checkInput();
    void changeImage(const QString &fileName);

    Ui::AddPhraseDialog *mUi;
    QPushButton *mOkPushButton;

private slots:
    void okPushButtonClicked();
    void on_englishPhraseLineEdit_textChanged(const QString &);
    void on_russianPhraseLineEdit_textChanged(const QString &);
    void on_loadImagePushButton_clicked();
};
//-----------------------------------------------------------------------------
#endif // ADDPHRASEDIALOG_H
