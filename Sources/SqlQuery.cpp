#include "SqlQuery.h"

#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>
#include <QSize>

#include <QDebug>
//-----------------------------------------------------------------------------
SqlQuery::SqlQuery(QSqlResult *sqlResult)
    : QSqlQuery(sqlResult)
{
}
//-----------------------------------------------------------------------------
SqlQuery::SqlQuery(const QString &query, QSqlDatabase db)
    : QSqlQuery(query, db)
{
}
//-----------------------------------------------------------------------------
bool SqlQuery::exec()
{
    bool result = QSqlQuery::exec();
    return processResult(result);
}
//-----------------------------------------------------------------------------
bool SqlQuery::exec(const QString &query)
{
    bool result = QSqlQuery::exec(query);
    return processResult(result);
}
//-----------------------------------------------------------------------------
QString SqlQuery::getLastExecutedQuery()
{
    QString query = lastQuery();
    QMapIterator<QString, QVariant> it(boundValues());
    while (it.hasNext()) {
        it.next();
        if (it.value().type() == QMetaType::QPixmap) { //%
            QPixmap pixmap = it.value().value<QPixmap>();
            QSize pixmapSize = pixmap.size();
            QString sizeStr = QString("(%1 x %2)")
                    .arg(pixmapSize.width())
                    .arg(pixmapSize.height());
            query.replace(it.key(), sizeStr);
        } else if (it.value().type() == QMetaType::QByteArray) {
            query.replace(it.key(), "QByteArray");
        } else {
            query.replace(it.key(), it.value().toString());
        }
    }
    return query;
}
//-----------------------------------------------------------------------------
bool SqlQuery::processResult(bool result)
{
    //%qDebug() << "SqlQuery::processResult: executedQuery:" << executedQuery();
    qDebug() << "SqlQuery::processResult: lastQuery           :" << lastQuery();
    qDebug() << "SqlQuery::processResult: getLastExecutedQuery:" << getLastExecutedQuery();

    if (result == false) {
        QMessageBox::warning(0, QObject::tr("Error")
                             , QObject::tr("Cannot execute a query!")
                             + QObject::tr("\nError code: ")
                             + QString::number(lastError().number())
                             + QObject::tr("\nError text: ")
                             + lastError().text());
    }
    return result;
}
//-----------------------------------------------------------------------------
