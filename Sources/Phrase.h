#ifndef PHRASE_H
#define PHRASE_H

#include <QString>
#include <QPixmap>
//-----------------------------------------------------------------------------
class Phrase
{
public:
    static const QString Tn; // Table name.
    static const QString IdCn; // ID column name.
    static const QString EngCn;
    static const QString RusCn;
    static const QString ImageCn;

    static const QSize ImageSize;

    Phrase(const QString &eng, const QString &rus, const QPixmap &image);

    const QString getEng() const;
    const QString getRus() const;
    const QPixmap getImage() const;

private:
    QString mEng;
    QString mRus;
    QPixmap mImage;
};
//-----------------------------------------------------------------------------
#endif // PHRASE_H
