#ifndef DB_H
#define DB_H

#include "Learner.h"
#include "Phrase.h"

#include <QString>

typedef qint64 Id;

//QT_BEGIN_NAMESPACE
//class Learner;
//QT_END_NAMESPACE
//-----------------------------------------------------------------------------
class Db
{
public:
    enum Status
    {
        Ok
        , Error
    };

    static Db *instance();
    static void deleteInstance();

    static Status getStatus();

    // Learner table methods:
    bool hasLearner(const Learner &learner);
    bool addLearner(const Learner &learner, Id &learnerId);
    Learner getLearner(Id learnerId);

    // Phrase table methods:
    bool addPhrase(const Phrase &phrase, Id *phraseId = 0);

protected:
    static Status createConnection();
    static Status createTables();

private:
    Db();
    ~Db();

    static Db *mDb;
    static Status mStatus;
};
//-----------------------------------------------------------------------------
QByteArray pixmapToByteArray(const QPixmap &pixmap);

#endif // DB_H
