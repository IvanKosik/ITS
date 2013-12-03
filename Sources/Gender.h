#ifndef GENDER_H
#define GENDER_H

#include <QObject>
//-----------------------------------------------------------------------------
class Gender
{
public:
    Gender();

    static const QString Tn; // Table name.
    static const QString IdCn; // ID column name.
    static const QString NameCn;

    enum Type
    {
        Indeterminate = 1 // Т.к. значения ID в БД начинаются c 1
        , Male = 2
        , Female = 3
    };

    static QString typeToStr(const Type type);
};
//-----------------------------------------------------------------------------
#endif // GENDER_H
