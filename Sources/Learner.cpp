#include "Learner.h"

#include <QPixmap>

#include <QDebug>

const QString Learner::Tn = "Learner"; // Learner table name.
const QString Learner::IdCn = "LearnerId"; // Learner ID column name.
const QString Learner::NicknameCn = "LearnerNickname";
const QString Learner::PasswordCn = "LearnerPassword";
const QString Learner::DescriptionCn = "LearnerDescription";
const QString Learner::AvatarCn = "LearnerAvatar";
//-----------------------------------------------------------------------------
Learner::Learner(const QString &nickname, const QString &password
                 , const QString &description, const Gender::Type genderType
                 , const QPixmap &avatar)
    : mNickname(nickname), mPassword(password), mDescription(description)
    , mGenderType(genderType), mAvatar(avatar)
{
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
void Learner::setGenderType(const Gender::Type genderType)
{
    mGenderType = genderType;
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
Gender::Type Learner::getGenderType() const
{
    return mGenderType;
}
//-----------------------------------------------------------------------------
QString Learner::getGenderStr() const
{
    return Gender::typeToStr(mGenderType);
}
//-----------------------------------------------------------------------------
QPixmap Learner::getAvatar() const
{
    return mAvatar;
}
//-----------------------------------------------------------------------------
