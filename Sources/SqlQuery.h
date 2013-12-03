#ifndef SQLQUERY_H
#define SQLQUERY_H

#include <QSqlQuery>
//-----------------------------------------------------------------------------
class SqlQuery : public QSqlQuery
{
public:
    explicit SqlQuery(QSqlResult *sqlResult);
    explicit SqlQuery(const QString &query = QString()
            , QSqlDatabase db = QSqlDatabase());

    bool exec();
    bool exec(const QString &query);
    bool execBatch(BatchExecutionMode mode = ValuesAsRows);

    QString getLastExecutedQuery();

protected:
    bool processResult(bool result);
};
//-----------------------------------------------------------------------------
#endif // SQLQUERY_H
