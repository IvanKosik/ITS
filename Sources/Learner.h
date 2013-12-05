#ifndef LEARNER_H
#define LEARNER_H

#include "Gender.h"

#include <QObject>
#include <QPixmap>

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE
//-----------------------------------------------------------------------------
class Learner
{
public:
    static const QString Tn; // Table name.
    static const QString IdCn; // ID column name.
    static const QString NicknameCn;
    static const QString PasswordCn;
    static const QString DescriptionCn;
    static const QString AvatarCn;
    static const QString ScoreCn;

    Learner(const QString &nickname = "", const QString &password = ""
            , const QString &description = ""
            , const Gender::Type genderType = Gender::Indeterminate
            , const QPixmap &avatar = QPixmap(), const qint32 score = 0);

    void setNickname(const QString &nickname);
    void setPassword(const QString &password);
    void setDescription(const QString &description);
    void setGenderType(const Gender::Type genderType);
    void setAvatar(const QPixmap &avatar);
    void setScore(const qint32 score);

    QString getNickname() const;
    QString getPassword() const;
    QString getDescription() const;
    Gender::Type getGenderType() const;
    QString getGenderStr() const;
    QPixmap getAvatar() const;
    qint32 getScore() const;

protected:
    QString mNickname;
    QString mPassword;
    QString mDescription;
    Gender::Type mGenderType;
    QPixmap mAvatar;
    qint32 mScore;
};
//-----------------------------------------------------------------------------
typedef QList<Learner> Learners;

#endif // LEARNER_H
