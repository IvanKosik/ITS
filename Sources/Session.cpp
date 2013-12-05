#include "Session.h"

Session *Session::mSession = 0;
//-----------------------------------------------------------------------------
Session *Session::instance()
{
    if (mSession == 0) {
        return mSession = new Session;
    }
    return mSession;
}
//-----------------------------------------------------------------------------
void Session::deleteInstance()
{
    if (mSession != 0) {
        delete mSession;
        mSession = 0;
    }
}
//-----------------------------------------------------------------------------
void Session::open(Id learnerId)
{
    mLearnerId = learnerId;
    mOpened = true;
    emit opened(mLearnerId);
}
//-----------------------------------------------------------------------------
void Session::close()
{
    mLearnerId = -1;
    mOpened = false;
    emit closed();
}
//-----------------------------------------------------------------------------
bool Session::wasOpen() const
{
    return mOpened;
}
//-----------------------------------------------------------------------------
Id Session::getLearnerId() const
{
    return mLearnerId;
}
//-----------------------------------------------------------------------------
Session::Session(QObject *parent) : QObject(parent)
{
    mLearnerId = -1;
    mOpened = false;
}
//-----------------------------------------------------------------------------
Session::~Session()
{
    deleteInstance();
}
//-----------------------------------------------------------------------------
