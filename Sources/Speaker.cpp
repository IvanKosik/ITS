#include "Speaker.h"

#include <QProcess>
#include <QTextCodec>

#include <QDebug>

Speaker *Speaker::mSpeaker = 0;

const QString Cmd = "cmd.exe";
const QString FestivalPath = "D:/Libs/Festival/festival/src/main/festival.exe";
//-----------------------------------------------------------------------------
Speaker *Speaker::instance()
{
    if (mSpeaker == 0) {
        return mSpeaker = new Speaker;
    }
    return mSpeaker;
}
//-----------------------------------------------------------------------------
void Speaker::deleteInstance()
{
    if (mSpeaker != 0) {
        delete mSpeaker;
        mSpeaker = 0;
    }
}
//-----------------------------------------------------------------------------
void Speaker::pronounce(const QString &phrase)
{
    QProcess process;
    QStringList args;
    /*args << "/c" << "echo. " + phrase + " | " + "\"" + FestivalPath + "\"" + " --tts";
    qDebug() << "speaker phrase:" << phrase;
    qDebug() << "args:" << args;*/

   // process.start(Cmd, args);

    args << "/c" << FestivalPath << "--tts";
    process.start(Cmd, args); //"echo. " + phrase + " | " + "\"" + FestivalPath + "\"" + " --tts");

    qDebug() << "arguments:" << process.arguments();
    if (!process.waitForStarted()) {
        qDebug() << "DOESNT START!";
        qDebug() << "readAll:" << process.readAll();
    }

//    process.write("Hello, World!\n");
    process.write(phrase.toStdString().c_str());


//    process.write("\nEOF!");

//    process.terminate();
//    process.write()


    //process.waitForReadyRead(3000);
    process.waitForFinished(100);


//    process.terminate();

/*   if (process.waitForFinished()) {
  //      process.close();

      /*  QTextCodec *ibm866TextCodec = QTextCodec::codecForName("IBM 866"); //% Р•СЃР»Рё СЂСѓСЃСЃРєРёР№ С‚РµРєСЃС‚ РЅРµ РЅСѓР¶РµРЅ, С‚Рѕ СЌС‚Рѕ РЅРµРЅСѓР¶РЅРѕ. Р СѓСЃСЃРєРёР№ РµСЃС‚СЊ, РµСЃР»Рё РЅРµС‚Сѓ СЌС‚РѕРіРѕ: chcp 1251 > nul (РёРјРµРЅРЅРѕ > nul)

        QByteArray statusByteArray = process.readAllStandardOutput();
        QString status = ibm866TextCodec->toUnicode(statusByteArray); //% Р•СЃР»Рё СЂСѓСЃСЃРєРёР№ С‚РµРєСЃС‚ РЅРµ РЅСѓР¶РµРЅ, С‚Рѕ СЌС‚Рѕ РЅРµРЅСѓР¶РЅРѕ.
        qDebug() << "status:" << status;*/
//    } else {
//        qDebug() << "ERROR!";
//    }
    /*qDebug() << "ReadAll_2:" << */process.readAll();

//    qDebug() << "error string" << process.errorString();*/
}
//-----------------------------------------------------------------------------
Speaker::Speaker(QObject *parent) : QObject(parent)
{
}
//-----------------------------------------------------------------------------
Speaker::~Speaker()
{
    deleteInstance();
}
//-----------------------------------------------------------------------------
