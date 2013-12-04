#ifndef DICTIONARYDIALOG_H
#define DICTIONARYDIALOG_H

#include <QDialog>

#include <QSqlTableModel>
//-----------------------------------------------------------------------------
namespace Ui
{
    class DictionaryDialog;
}
//-----------------------------------------------------------------------------
class DictionaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DictionaryDialog(QWidget *parent = 0);
    ~DictionaryDialog();

private slots:
    void on_addPhrasePushButton_clicked();

private:
    Ui::DictionaryDialog *mUi;
    QSqlTableModel *mPhraseModel;
};
//-----------------------------------------------------------------------------
#endif // DICTIONARYDIALOG_H
