#include "LoginDialog.h"
#include "ui_LoginDialog.h"

#include "Learner.h"
#include "ImageDelegate.h"
#include "Db.h"
#include "SqlQuery.h"
#include "Gender.h"

#include <QtWidgets>
#include <QSqlQueryModel>
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
    mLearnerModel = new QSqlQueryModel;
    SqlQuery learnerQuery;
    learnerQuery.prepare(QString("SELECT %1, %2, %3, %4, %5, %6 FROM %7 INNER JOIN %8 ON %7.%9 = %8.%9")
                         .arg(Learner::IdCn, Learner::NicknameCn, Learner::PasswordCn
                              , Gender::NameCn, Learner::DescriptionCn, Learner::AvatarCn
                              , Learner::Tn, Gender::Tn, Gender::IdCn));
    learnerQuery.exec();
    mLearnerModel->setQuery(learnerQuery);

    mLearnerModel->setHeaderData(0, Qt::Horizontal, "ID");
    mLearnerModel->setHeaderData(1, Qt::Horizontal, "Nickname");
    mLearnerModel->setHeaderData(2, Qt::Horizontal, "Password");
    mLearnerModel->setHeaderData(3, Qt::Horizontal, "Gender");
    mLearnerModel->setHeaderData(4, Qt::Horizontal, "Description");
    mLearnerModel->setHeaderData(5, Qt::Horizontal, "Avatar");

    mUi->learnerTableView->setModel(mLearnerModel);
    mUi->learnerTableView->setItemDelegateForColumn(5, new ImageDelegate(mUi->learnerTableView));

    mUi->learnerTableView->setColumnHidden(0, true); // ID
    mUi->learnerTableView->setColumnHidden(2, true); // Password
    mUi->learnerTableView->setColumnHidden(4, true); // Description

    mUi->learnerTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(mUi->learnerTableView->selectionModel()
            , SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &))
            , SLOT(currentLearnerChanged(const QModelIndex &, const QModelIndex &)));

    mDataWidgetMapper = new QDataWidgetMapper;
    mDataWidgetMapper->setModel(mLearnerModel);
    mDataWidgetMapper->addMapping(mUi->descriptionTextEdit, 4);
    mDataWidgetMapper->toFirst();


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
void LoginDialog::currentLearnerChanged(const QModelIndex &current
                                        , const QModelIndex &)
{
    mDataWidgetMapper->setCurrentIndex(current.row());
}
//-----------------------------------------------------------------------------
