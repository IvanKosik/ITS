#include "Db.h"

#include "SqlQuery.h"
#include "Learner.h"
#include "Phrase.h"

#include <QSqlDatabase>
#include <QMessageBox>
#include <QApplication>
#include <QBuffer>

#include <QDebug>

Db *Db::mDb = 0;
Db::Status Db::mStatus = Db::Ok;
//-----------------------------------------------------------------------------
Db *Db::instance()
{
    if (mDb == 0) {
        return mDb = new Db;
    }
    return mDb;
}
//-----------------------------------------------------------------------------
void Db::deleteInstance()
{
    if (mDb != 0) {
        delete mDb;
        mDb = 0;
    }
}
//-----------------------------------------------------------------------------
Db::Status Db::getStatus()
{
    return mStatus;
}
//-----------------------------------------------------------------------------
bool Db::hasLearner(const Learner &learner)
{
    SqlQuery findQuery;
    findQuery.prepare(QString("SELECT * FROM %1 WHERE %2 = :nickname")
                      .arg(Learner::Tn, Learner::NicknameCn));
    findQuery.bindValue(":nickname", learner.getNickname());
    findQuery.exec();
    return findQuery.first();
}
//-----------------------------------------------------------------------------
bool Db::addLearner(const Learner &learner, Id &learnerId)
{
    SqlQuery insertQuery;
    insertQuery.prepare(QString("INSERT INTO %1 VALUES (NULL, :nickname, :password"
                                ", :gender, :description, :avatar, :score)")
                        .arg(Learner::Tn));
    insertQuery.bindValue(":nickname", learner.getNickname());
    insertQuery.bindValue(":password", learner.getPassword());
    insertQuery.bindValue(":gender", learner.getGenderType());
    insertQuery.bindValue(":description", learner.getDescription());
    insertQuery.bindValue(":avatar", pixmapToByteArray(learner.getAvatar()));
    insertQuery.bindValue(":score", learner.getScore());
    bool result = insertQuery.exec();
    learnerId = insertQuery.lastInsertId().toLongLong();
    return result;
}
//-----------------------------------------------------------------------------
Learner Db::getLearner(Id learnerId)
{
    SqlQuery findQuery;
    findQuery.prepare(QString("SELECT * FROM %1 WHERE %2 = :id")
                      .arg(Learner::Tn, Learner::IdCn));
    findQuery.bindValue(":id", learnerId);
    findQuery.exec();

    Learner learner;
    // If DB contains learner with such ID:
    if (findQuery.first()) {
        QString nickname = findQuery.value(Learner::NicknameCn).toString();
        QString password = findQuery.value(Learner::PasswordCn).toString();
        QString description = findQuery.value(Learner::DescriptionCn).toString();
        Gender::Type genderType = static_cast<Gender::Type>
                (findQuery.value(Gender::IdCn).toInt());
        QPixmap avatar;
        avatar.loadFromData(findQuery.value(Learner::AvatarCn).toByteArray());
        qint32 score = findQuery.value(Learner::ScoreCn).toInt();
        learner = Learner(nickname, password, description, genderType, avatar, score);
    }
    return learner;
}
//-----------------------------------------------------------------------------
bool Db::updateLearnerScore(Id learnerId, qint32 newScore)
{
    SqlQuery updateQuery;
    updateQuery.prepare(QString("UPDATE %1 SET %2 = :score WHERE %3 = :id")
                      .arg(Learner::Tn, Learner::ScoreCn, Learner::IdCn));
    updateQuery.bindValue(":score", newScore);
    updateQuery.bindValue(":id", learnerId);
    return updateQuery.exec();

    //%UPDATE Books SET Author='Lev Nikolayevich Tolstoy' WHERE Id=1;
}
//-----------------------------------------------------------------------------
bool Db::addPhrase(const Phrase &phrase, Id *phraseId)
{
    SqlQuery insertQuery;
    insertQuery.prepare(QString("INSERT INTO %1 VALUES (NULL, :eng, :rus, :image)")
                        .arg(Phrase::Tn));
    insertQuery.bindValue(":eng", phrase.getEng());
    insertQuery.bindValue(":rus", phrase.getRus());
    insertQuery.bindValue(":image", pixmapToByteArray(phrase.getImage()));
    bool result = insertQuery.exec();

    if (phraseId) {
        *phraseId = insertQuery.lastInsertId().toLongLong();
    }
    return result;
}
//-----------------------------------------------------------------------------
Phrases Db::getPhrases()
{
    SqlQuery findQuery;
    findQuery.prepare(QString("SELECT * FROM %1").arg(Phrase::Tn));
    findQuery.exec();

    Phrases phrases;
    while (findQuery.next()) {
        QString eng = findQuery.value(Phrase::EngCn).toString();
        QString rus = findQuery.value(Phrase::RusCn).toString();
        QPixmap image;
        image.loadFromData(findQuery.value(Phrase::ImageCn).toByteArray());

        Phrase phrase;
        phrase = Phrase(eng, rus, image);
        phrases.append(phrase);
    }
    return phrases;
}
//-----------------------------------------------------------------------------
Db::Status Db::createConnection()
{
    QSqlDatabase sqlDatabase = QSqlDatabase::addDatabase("QSQLITE");
    //%sqlDatabase.setDatabaseName(":memory:");
    sqlDatabase.setDatabaseName("D:/Projects/C++/Qt/5.1.1/ITS/Db.db");
    if (!sqlDatabase.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open DB")
                              , qApp->tr("Unable to establish a DB connection."
                                         "\nThis application needs SQLite support."
                                         " Please read the Qt SQL driver documentation"
                                         " for information how to build it."
                                         "\n\nClick Cancel to exit.")
                              , QMessageBox::Cancel);
        return Error;
    }
    return Ok;
}
//-----------------------------------------------------------------------------
Db::Status Db::createTables()
{
    Status status = Ok;

    SqlQuery createTableQuery;
    // Gender table:
    createTableQuery.prepare(QString("CREATE TABLE IF NOT EXISTS %1"
                                     "( %2 INTEGER NOT NULL UNIQUE"
                                     ", %3 TEXT    NOT NULL UNIQUE"
                                     ", PRIMARY KEY(%2)           )")
                             .arg(Gender::Tn, Gender::IdCn, Gender::NameCn));
    if (!createTableQuery.exec()) {
        qDebug() << "Unable to create the Gender table!";
        status = Error;
    }
    // Insert data into the Gender table:
    SqlQuery insertQuery;
    insertQuery.prepare(QString("INSERT OR IGNORE INTO %1 VALUES (NULL, ?)")
                        .arg(Gender::Tn));
    QVariantList names;
    names << "Indeterminate" << "Male" << "Female";
    insertQuery.addBindValue(names);
    if (!insertQuery.execBatch()) {
        qDebug() << "Unable to insert data into the Gender table!";
        status = Error;
    }

    // Learner table:
    createTableQuery.prepare(QString("CREATE TABLE IF NOT EXISTS %1"
                                     "( %2 INTEGER NOT NULL UNIQUE"
                                     ", %3 TEXT    NOT NULL UNIQUE"
                                     ", %4 TEXT                   "
                                     ", %5 INTEGER NOT NULL       "
                                     ", %6 TEXT                   "
                                     ", %7 BLOB                   "
                                     ", %8 INTEGER                "
                                     ", PRIMARY KEY(%2)           "
                                     ", FOREIGN KEY(%5) REFERENCES %9(%5))")
                             .arg(Learner::Tn, Learner::IdCn
                                  , Learner::NicknameCn, Learner::PasswordCn
                                  , Gender::IdCn, Learner::DescriptionCn
                                  , Learner::AvatarCn, Learner::ScoreCn
                                  , Gender::Tn));
    if (!createTableQuery.exec()) {
        qDebug() << "Unable to create the Learner table!";
        status = Error;
    }

    // Phrase table:
    createTableQuery.prepare(QString("CREATE TABLE IF NOT EXISTS %1"
                                     "( %2 INTEGER NOT NULL UNIQUE"
                                     ", %3 TEXT    NOT NULL       "
                                     ", %4 TEXT    NOT NULL       "
                                     ", %5 BLOB                   "
                                     ", PRIMARY KEY(%2)           )")
                             .arg(Phrase::Tn, Phrase::IdCn
                                  , Phrase::EngCn, Phrase::RusCn
                                  , Phrase::ImageCn));
    if (!createTableQuery.exec()) {
        qDebug() << "Unable to create the Phrase table!";
        status = Error;
    }


    /*%if (!sqlQuery.exec("CREATE TABLE Rus("
        "RusId     INTEGER NOT NULL, "
        "EngId     INTEGER NOT NULL, "
        "RusPhrase TEXT    NOT NULL, "
        "PRIMARY KEY(RusId)        , "
        "FOREIGN KEY(EngId)                       "
            "REFERENCES Eng(EngId) )")
    ) qDebug() << "Unable to create the Rus table!";%*/

    return status;
}
//-----------------------------------------------------------------------------
Db::Db()
{
    if ((mStatus = createConnection()) == Ok) {
        mStatus = createTables();
    }
}
//-----------------------------------------------------------------------------
Db::~Db()
{
    deleteInstance();
}
//-----------------------------------------------------------------------------
QByteArray pixmapToByteArray(const QPixmap &pixmap)
{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG"); //%! Если не указать формат, то не работает!
    return byteArray;
}
//-----------------------------------------------------------------------------
