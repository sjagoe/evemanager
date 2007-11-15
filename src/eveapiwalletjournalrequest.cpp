//#include "eveapiwalletjournalrequest.hh"
//
///*!
//pass the constructor args to the super-class
//*/
//EveApiWalletJournalRequest::EveApiWalletJournalRequest(
//    const QString& requestType, const QString& dataPath,
//    const int& xmlIndent, QObject* parent )
//        : EveApiCharacterRequest( requestType, dataPath, xmlIndent, parent )
//{
//
//}
//
///*!
//Check the paramaters
//*/
//bool EveApiWalletJournalRequest::validateParamaters(
//    const QMap<QString, QString>& parameters, QUrl& url )
//{
//    //required
//    QString userID = parameters.value("userID");
//    QString charID = parameters.value("characterID");
//    QString apiKey = parameters.value("apiKey");
//    if (( userID.isNull() ) || ( charID.isNull() ) || ( apiKey.isNull() ))
//    {
//        return false;
//    }
//    url.addQueryItem("userID", userID);
//    url.addQueryItem("characterID", charID);
//    url.addQueryItem("apiKey", apiKey);
//
//    // optional
//    QString accountKey = parameters.value("accountKey");
//    QString beforeRefID = parameters.value("beforeRefID");
//    if (!accountKey.isNull())
//    {
//        url.addQueryItem("accountKey", accountKey);
//    }
//    if (!beforeRefID.isNull())
//    {
//        url.addQueryItem("beforeRefID", beforeRefID);
//    }
//
//    return true;
//}
//
