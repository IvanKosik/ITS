#include "Learner.h"

#include <QPixmap>

#include <QDebug>

const QString Learner::Tn = "Learner"; // Learner table name.
const QString Learner::IdCn = "LearnerId"; // Learner ID column name.
const QString Learner::NicknameCn = "LearnerNickname";
const QString Learner::PasswordCn = "LearnerPassword";
const QString Learner::GenderCn = "LearnerGender";
const QString Learner::DescriptionCn = "LearnerDescription";
const QString Learner::AvatarCn = "LearnerAvatar";
//-----------------------------------------------------------------------------
QString Learner::genderToStr(const Learner::Gender gender)
{
    switch (gender) {
    case Indeterminate:
        return "Indeterminate";
    case Male:
        return "Male";
    case Female:
        return "Female";
    }
    return "Unknown gender";
}
//-----------------------------------------------------------------------------
Learner::Learner(const QString &nickname, const QString &password
                 , const QString &description, const Learner::Gender gender
                 , const QPixmap &avatar)
    : mNickname(nickname), mPassword(password), mDescription(description)
    , mGender(gender), mAvatar(avatar)
{
    qDebug() << "Learner pixmap:" << avatar;
}
//-----------------------------------------------------------------------------
void Learner::setNickname(const QString &nickname)
{
    mNickname = nickname;
}
//-----------------------------------------------------------------------------
void Learner::setPassword(const QString &password)
{
    mPassword = password;
}
//-----------------------------------------------------------------------------
void Learner::setDescription(const QString &description)
{
    mDescription = description;
}
//-----------------------------------------------------------------------------
void Learner::setGender(const Learner::Gender gender)
{
    mGender = gender;
}
//-----------------------------------------------------------------------------
void Learner::setAvatar(const QPixmap &avatar)
{
    mAvatar = avatar;
}
//-----------------------------------------------------------------------------
QString Learner::getNickname() const
{
    return mNickname;
}
//-----------------------------------------------------------------------------
QString Learner::getPassword() const
{
    return mPassword;
}
//-----------------------------------------------------------------------------
QString Learner::getDescription() const
{
    return mDescription;
}
//-----------------------------------------------------------------------------
Learner::Gender Learner::getGender() const
{
    return mGender;
}
//-----------------------------------------------------------------------------
QString Learner::getGenderStr() const
{
    return genderToStr(mGender);
}
//-----------------------------------------------------------------------------
QPixmap Learner::getAvatar() const
{
    return mAvatar;
}
//-----------------------------------------------------------------------------
