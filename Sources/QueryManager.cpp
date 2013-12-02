#include "QueryManager.h"

#include "SqlQuery.h"

#include <QStringList>

#include <QDebug>

QueryManager *QueryManager::mQueryManager = 0;
//-----------------------------------------------------------------------------
QueryManager *QueryManager::instance()
{
    if (mQueryManager == 0) {
        return mQueryManager = new QueryManager;
    }
    return mQueryManager;
}
//-----------------------------------------------------------------------------
void QueryManager::deleteInstance()
{
    if (mQueryManager != 0) {
        delete mQueryManager;
        mQueryManager = 0;
    }
}
//-----------------------------------------------------------------------------
QSqlQuery QueryManager::execQuery(const QString &query
                                  , const QVariantList &bindValues)
{
    qDebug() << "QueryManager::execQuery: query:" << query;
    SqlQuery sqlQuery(query);
    qDebug() << "QueryManager::execQuery: executedQuery:" << sqlQuery.executedQuery();
    qDebug() << "QueryManager::execQuery: lastQuery:" << sqlQuery.lastQuery();
    foreach (QVariant bindValue, bindValues) {
        sqlQuery.addBindValue(bindValue);
    }
    qDebug() << "QueryManager::execQuery: after bind executedQuery:" << sqlQuery.executedQuery();
    qDebug() << "QueryManager::execQuery: after bind lastQuery:" << sqlQuery.lastQuery();

    sqlQuery.exec();

    qDebug() << "QueryManager::execQuery: after exec executedQuery:" << sqlQuery.executedQuery();
    qDebug() << "QueryManager::execQuery: after exec lastQuery:" << sqlQuery.lastQuery();

    return sqlQuery;
}
//-----------------------------------------------------------------------------
QSqlQuery QueryManager::execSelectQuery(const QString &tableName
                                        , const QStringList &columns
                                        , const QString &condition
                                        , const QVariantList &bindValues)
{
    QString query;
    query += "SELECT";
    foreach (QString column, columns) {
        query += " " + column; //%! Запятые, еще возможно скобки
    }
    query += " FROM";
    query += " " + tableName;
    if (!condition.isEmpty()) {
        query += " WHERE";
        query += " " + condition;
    }
    return execQuery(query, bindValues);
}
//-----------------------------------------------------------------------------
QSqlQuery QueryManager::execSelectAllQuery(const QString &tableName
                                           , const QString &condition
                                           , const QVariantList &bindValues)
{
    QStringList columns;
    columns << "*";
    return execSelectQuery(tableName, columns, condition, bindValues);
}
//-----------------------------------------------------------------------------
QSqlQuery QueryManager::execInsertQuery(const QString &tableName, const QStringList values, const QVariantList &bindValues)
{
    return QSqlQuery();
}
//-----------------------------------------------------------------------------
QueryManager::QueryManager()
{
}
//-----------------------------------------------------------------------------
QueryManager::~QueryManager()
{
}
//-----------------------------------------------------------------------------
