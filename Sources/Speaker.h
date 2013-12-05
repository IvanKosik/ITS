#ifndef SPEAKER_H
#define SPEAKER_H

#include <QObject>
//-----------------------------------------------------------------------------
class Speaker : public QObject
{
    Q_OBJECT

public:
    static Speaker *instance();
    static void deleteInstance();

    static void pronounce(const QString &phrase);

private:
    Speaker(QObject *parent = 0);
    ~Speaker();

    static Speaker *mSpeaker;
};
//-----------------------------------------------------------------------------
#endif // SPEAKER_H
