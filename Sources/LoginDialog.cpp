#include "LoginDialog.h"
#include "ui_LoginDialog.h"

#include "Learner.h"
#include "ImageDelegate.h"
#include "GenderDelegate.h"
#include "Db.h"

#include <QtWidgets>
#include <QSqlTableModel>
//-----------------------------------------------------------------------------
LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , mUi(new Ui::LoginDialog)
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


    // Display learners:
    mLearnerModel = new QSqlTableModel; //%! delete or try without 'new'
    mLearnerModel->setTable(Learner::Tn);
    mLearnerModel->setHeaderData(0, Qt::Horizontal, "ID");
    mLearnerModel->setHeaderData(1, Qt::Horizontal, "Nickname");
    mLearnerModel->setHeaderData(2, Qt::Horizontal, "Password");
    mLearnerModel->setHeaderData(3, Qt::Horizontal, "Gender");
    mLearnerModel->setHeaderData(4, Qt::Horizontal, "Description");
    mLearnerModel->setHeaderData(5, Qt::Horizontal, "Avatar");
    mLearnerModel->select();

    mUi->learnerTableView->setModel(mLearnerModel);
    mUi->learnerTableView->setItemDelegateForColumn(5, new ImageDelegate(mUi->learnerTableView));
    mUi->learnerTableView->setItemDelegateForColumn(3, new GenderDelegate(mUi->learnerTableView));

    mUi->learnerTableView->setColumnHidden(0, true);
    mUi->learnerTableView->setColumnHidden(2, true);
    mUi->learnerTableView->setColumnHidden(4, true);

    mUi->learnerTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    exec();
}
//-----------------------------------------------------------------------------
LoginDialog::~LoginDialog()
{
    delete mUi;
    delete mLearnerModel;
}
//-----------------------------------------------------------------------------
void LoginDialog::okPushButtonClicked()
{
    qint32 curRow = mUi->learnerTableView->currentIndex().row();
    Id learnerId = mLearnerModel->data(mLearnerModel->index(curRow, 0)).toLongLong();
    Learner learner = Db::instance()->getLearner(learnerId);
}
//-----------------------------------------------------------------------------
