#ifndef SESSION_H
#define SESSION_H

#include "Db.h"
//-----------------------------------------------------------------------------
class Session : public QObject
{
    Q_OBJECT

public:
    static Session *instance();
    static void deleteInstance();

    void open(Id learnerId);
    void close();

    bool wasOpen() const;

private:
    Session(QObject *parent = 0);
    ~Session();

    static Session *mSession;

    Id mLearnerId;
    bool mOpened;

signals:
    void opened(Id learnerId);
    void closed();
};
//-----------------------------------------------------------------------------
#endif // SESSION_H
