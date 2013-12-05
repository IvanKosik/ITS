#ifndef PHRASE_H
#define PHRASE_H

#include <QString>
#include <QPixmap>

#include <iostream>
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

    Phrase(const QString &eng = "", const QString &rus = ""
            , const QPixmap &image = QPixmap());

    const QString getEng() const;
    const QString getRus() const;
    const QPixmap getImage() const;

    friend std::ostream &operator <<(std::ostream &os, const Phrase &phrase);

private:
    QString mEng;
    QString mRus;
    QPixmap mImage;
};
//-----------------------------------------------------------------------------
typedef QList<Phrase> Phrases;

#endif // PHRASE_H
