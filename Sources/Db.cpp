#include "Db.h"

#include "SqlQuery.h"
#include "Learner.h"

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
//    return findQuery.first();

    findQuery.first();

//    QPixmap pixmap = findQuery.value(Learner::AvatarCn).value<QPixmap>();
//    QSize pixmapSize = pixmap.size();
//    QString sizeStr = QString("(%1 x %2)")
//            .arg(pixmapSize.width())
//            .arg(pixmapSize.height());
    QByteArray byteArray = findQuery.value(Learner::AvatarCn).toByteArray();
    qDebug() << "byteArray:" << byteArray;
    QPixmap pixmap;
    pixmap.loadFromData(byteArray);

//    QPixmap pixmap = findQuery.value(Learner::AvatarCn).value<QPixmap>();
    qDebug() << pixmap;
    qDebug() << "description:" << findQuery.value(Learner::DescriptionCn);

    return findQuery.first();
    /*QString condition = Learner::NicknameCn + " = ?";
    QVariantList bindValues;
    bindValues << learner.getNickname();
    QSqlQuery findQuery
            = QueryManager::instance()->execSelectAllQuery(Learner::Tn
                                                           , condition
                                                           , bindValues);
    return findQuery.first();*/
}
//-----------------------------------------------------------------------------
bool Db::addLearner(const Learner &learner)
{
//    QStringList values;
//    values << "NULL" << "?" << "?";
//    QVariantList bindValues;
//    bindValues << learner.getNickname();
//    bindValues << learner.getPassword();
//    QSqlQuery insertQuery = QueryManager::instance()->execInsertQuery(Learner::Tn
//                                                                      , values
//                                                                      , bindValues);

//    QSqlQuery insertQuery("INSERT INTO Learner (LearnerId, LearnerNickname, LearnerPassword) VALUES (NULL, ?, ?)");

//    QSqlQuery insertQuery("INSERT INTO Learner VALUES (NULL, ?, ?)");
    SqlQuery insertQuery;

    insertQuery.prepare(QString("INSERT INTO %1 VALUES (NULL, :nickname, :password"
                                ", :gender, :description, :avatar)")
                        .arg(Learner::Tn));
//    insertQuery.bindValue(":tn", QVariant("Learner"));
//    insertQuery.addBindValue("Learner");
    qDebug() << "getAvatar:" << learner.getAvatar();
//    qDebug() << "getAvatar.toString:" << learner.getAvatar();

    insertQuery.bindValue(":nickname", learner.getNickname());
    insertQuery.bindValue(":password", learner.getPassword());
    insertQuery.bindValue(":gender", learner.getGenderType());
    insertQuery.bindValue(":description", learner.getDescription());
    insertQuery.bindValue(":avatar", pixmapToByteArray(learner.getAvatar()));
    return insertQuery.exec();
//    insertQuery.addBindValue(learner.getNickname());
//    insertQuery.addBindValue(learner.getPassword());

//    return insertQuery.exec();

         /*       if (!insertQuery.exec()) {
                    QMessageBox::warning(0, QObject::tr("Error"), QObject::tr("Cannot execute query to insert into Eng table!")
                                         + QObject::tr("\nError code: ") + QString::number(insertQuery.lastError().number())
                                         + QObject::tr("\nError text: ") + insertQuery.lastError().text());
                    return false;
                }

                return true;*/
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
        learner = Learner(nickname, password, description, genderType, avatar);
    }
    return learner;
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
    insertQuery.execBatch();


    // Learner table:
    createTableQuery.prepare(QString("CREATE TABLE IF NOT EXISTS %1"
                                     "( %2 INTEGER NOT NULL UNIQUE"
                                     ", %3 TEXT    NOT NULL UNIQUE"
                                     ", %4 TEXT                   "
                                     ", %5 INTEGER NOT NULL       "
                                     ", %6 TEXT                   "
                                     ", %7 BLOB                   "
                                     ", PRIMARY KEY(%2)           "
                                     ", FOREIGN KEY(%5) REFERENCES %8(%5))")
                             .arg(Learner::Tn, Learner::IdCn
                                  , Learner::NicknameCn, Learner::PasswordCn
                                  , Gender::IdCn, Learner::DescriptionCn
                                  , Learner::AvatarCn, Gender::Tn));
    if (!createTableQuery.exec()) {
        qDebug() << "Unable to create the Learner table!";
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
}
//-----------------------------------------------------------------------------
QByteArray pixmapToByteArray(const QPixmap &pixmap)
{
//    qDebug() << "pixmap:" << pixmap;
//    QSqlQuery qry(dbName);
//    QPixmap pixmap("myFile.png", "PNG");
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG");//%, "PNG");  //%! Если не указать формат, то не работает!

//    QPixmap p2;
//    p2.loadFromData(byteArray);

//    qDebug() << "pixmapToByteArray:" << byteArray;
//    qDebug() << "p2:" << p2;
//    qry.prepare("INSERT INTO table (blobField) VALUES (?);");
//    qry.addBindValue(QVariant(bytes));
    return byteArray;
}
//-----------------------------------------------------------------------------
