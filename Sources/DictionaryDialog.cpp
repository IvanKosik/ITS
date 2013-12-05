#include "DictionaryDialog.h"
#include "ui_DictionaryDialog.h"

#include "Phrase.h"
#include "ImageDelegate.h"
#include "AddPhraseDialog.h"
#include "Speaker.h"

#include <QSqlTableModel>
//-----------------------------------------------------------------------------
DictionaryDialog::DictionaryDialog(QWidget *parent)
    : QDialog(parent)
    , mUi(new Ui::DictionaryDialog)
{
    mUi->setupUi(this);


    // Display dictionary phrases:
    mPhraseModel = new QSqlTableModel;
    mPhraseModel->setTable(Phrase::Tn);
    mPhraseModel->select();

    mPhraseModel->setHeaderData(0, Qt::Horizontal, "ID");
    mPhraseModel->setHeaderData(1, Qt::Horizontal, "English");
    mPhraseModel->setHeaderData(2, Qt::Horizontal, "Russian");
    mPhraseModel->setHeaderData(3, Qt::Horizontal, "Image");

    mUi->dictionaryTableView->setModel(mPhraseModel);
    mUi->dictionaryTableView->setItemDelegateForColumn(3, new ImageDelegate(mUi->dictionaryTableView));

    mUi->dictionaryTableView->setColumnHidden(0, true); // ID

    mUi->dictionaryTableView->horizontalHeader()
            ->setSectionResizeMode(QHeaderView::Stretch);

    /*connect(mUi->learnerTableView->selectionModel()
            , SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &))
            , SLOT(currentLearnerChanged(const QModelIndex &, const QModelIndex &)));
*/

    exec();
}
//-----------------------------------------------------------------------------
DictionaryDialog::~DictionaryDialog()
{
    delete mUi;
    delete mPhraseModel;
}
//-----------------------------------------------------------------------------
void DictionaryDialog::on_addPhrasePushButton_clicked()
{
    if (AddPhraseDialog(this).result() == QDialog::Accepted) {
        mPhraseModel->select();
    }
}
//-----------------------------------------------------------------------------
void DictionaryDialog::on_pronouncePhrasePushButton_clicked()
{
    qint32 row = mUi->dictionaryTableView->currentIndex().row();
    Speaker::instance()->pronounce(mPhraseModel->data(mPhraseModel->index(row, 1)).toString());
}
//-----------------------------------------------------------------------------
