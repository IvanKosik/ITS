#include "Phrase.h"

const QString Phrase::Tn = "Phrase"; // Phrase table name.
const QString Phrase::IdCn = "PhraseId"; // Phrase ID column name.
const QString Phrase::EngCn = "PhraseEng";
const QString Phrase::RusCn = "PhraseRus";
const QString Phrase::ImageCn = "PhraseImage";

const QSize Phrase::ImageSize = QSize(256, 256);
//-----------------------------------------------------------------------------
Phrase::Phrase(const QString &eng, const QString &rus, const QPixmap &image)
    : mEng(eng), mRus(rus), mImage(image)
{
}
//-----------------------------------------------------------------------------
const QString Phrase::getEng() const
{
    return mEng;
}
//-----------------------------------------------------------------------------
const QString Phrase::getRus() const
{
    return mRus;
}
//-----------------------------------------------------------------------------
const QPixmap Phrase::getImage() const
{
    return mImage;
}
//-----------------------------------------------------------------------------
