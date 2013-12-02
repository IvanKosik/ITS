#ifndef QUERYMANAGER_H
#define QUERYMANAGER_H

#include <QString>
#include <QVariantList>

QT_BEGIN_NAMESPACE
class QSqlQuery;
QT_END_NAMESPACE
//-----------------------------------------------------------------------------
class QueryManager
{
public:
    /*%enum QueryType
    {
        Select
        , Insert
    };*/

    static QueryManager *instance();
    static void deleteInstance();

    QSqlQuery execQuery(const QString &query
                        , const QVariantList &bindValues = QVariantList());

    QSqlQuery execSelectQuery(const QString &tableName
                              , const QStringList &columns, const QString &condition = ""
                              , const QVariantList &bindValues = QVariantList());

    QSqlQuery execSelectAllQuery(const QString &tableName
                                 , const QString &condition = ""
                                 , const QVariantList &bindValues = QVariantList());

    QSqlQuery execInsertQuery(const QString &tableName
                              , const QStringList values
                              , const QVariantList &bindValues = QVariantList());

private:
    QueryManager();
    ~QueryManager();

    static QueryManager *mQueryManager;
};
//-----------------------------------------------------------------------------
#endif // QUERYMANAGER_H
