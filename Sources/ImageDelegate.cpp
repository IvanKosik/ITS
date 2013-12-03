#include "ImageDelegate.h"

#include <QPainter>

#include <QDebug>
//-----------------------------------------------------------------------------
ImageDelegate::ImageDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}
//-----------------------------------------------------------------------------
void ImageDelegate::paint(QPainter *painter
                          , const QStyleOptionViewItem &option
                          , const QModelIndex &index) const
{
    QByteArray byteArray = index.data().toByteArray();
    QPixmap pixmap;
    pixmap.loadFromData(byteArray);
    if (pixmap.isNull()) {
        QStyledItemDelegate::paint(painter, option, index);
    } else {

        if (option.state & QStyle::State_Selected) {
            painter->fillRect(option.rect, option.palette.highlight());
        }

        pixmap = pixmap.scaled(option.rect.width(), option.rect.height()
                               , Qt::KeepAspectRatio, Qt::SmoothTransformation);

        QPointF pixmapPoint = QPointF(option.rect.center().x() - pixmap.width() / 2.
                                      , option.rect.center().y() - pixmap.height() / 2.);

        painter->drawPixmap(pixmapPoint, pixmap);
    }
}
//-----------------------------------------------------------------------------
