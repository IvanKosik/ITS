#include "Gender.h"

#include <QDebug>

const QString Gender::Tn = "Gender"; // Gender table name.
const QString Gender::IdCn = "GenderId"; // Gender ID column name.
const QString Gender::NameCn = "GenderName";
//-----------------------------------------------------------------------------
Gender::Gender()
{
}
//-----------------------------------------------------------------------------
QString Gender::typeToStr(const Type type)
{
    switch (type) {
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
