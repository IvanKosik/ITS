#include "GenderDelegate.h"

#include "Learner.h"

#include <QPainter>

#include <QDebug>
//-----------------------------------------------------------------------------
GenderDelegate::GenderDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}
//-----------------------------------------------------------------------------
void GenderDelegate::paint(QPainter *painter
                          , const QStyleOptionViewItem &option
                          , const QModelIndex &index) const
{
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
    }

    Learner::Gender gender = static_cast<Learner::Gender>(index.data().toInt());
    QString genderStr = Learner::genderToStr(gender);

    painter->drawText(option.rect, genderStr);

//    QStyledItemDelegate::paint(painter, optionn, index);
}
//-----------------------------------------------------------------------------
