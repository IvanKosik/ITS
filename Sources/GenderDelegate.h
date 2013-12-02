#ifndef GENDERDELEGATE_H
#define GENDERDELEGATE_H

#include <QStyledItemDelegate>
//-----------------------------------------------------------------------------
class GenderDelegate : public QStyledItemDelegate
{
public:
    explicit GenderDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option
               , const QModelIndex &index) const;
};
//-----------------------------------------------------------------------------
#endif // GENDERDELEGATE_H
