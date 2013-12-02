#ifndef LEARNER_H
#define LEARNER_H

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
    static const QString GenderCn;
    static const QString DescriptionCn;
    static const QString AvatarCn;

    enum Gender
    {
        Indeterminate
        , Male
        , Female
    };

    static QString genderToStr(const Gender gender);

    Learner(const QString &nickname = "", const QString &password = ""
            , const QString &description = "", const Gender gender = Indeterminate
            , const QPixmap &avatar = QPixmap());

    void setNickname(const QString &nickname);
    void setPassword(const QString &password);
    void setDescription(const QString &description);
    void setGender(const Gender gender);
    void setAvatar(const QPixmap &avatar);

    QString getNickname() const;
    QString getPassword() const;
    QString getDescription() const;
    Gender getGender() const;
    QString getGenderStr() const;
    QPixmap getAvatar() const;

protected:
    QString mNickname;
    QString mPassword;
    QString mDescription;
    Gender mGender;
    QPixmap mAvatar;
};
//-----------------------------------------------------------------------------
typedef QList<Learner> Learners;

#endif // LEARNER_H
