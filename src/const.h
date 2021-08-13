#ifndef HTTP_SERVER_CONST_H
#define HTTP_SERVER_CONST_H


#include <QMetaType>
#include <QRegularExpressionMatch>
#include <QtPromise>

#include "HttpData.h"


using QtPromise::QPromiseTimeoutException;
using QtPromise::QPromise;
using HttpDataPtr = std::shared_ptr<HttpData>;
using HttpPromise = QPromise<HttpDataPtr>;
using HttpFunc = std::function<HttpPromise(HttpDataPtr)>;
using HttpResolveFunc = const QtPromise::QPromiseResolve<HttpDataPtr> &;
using HttpRejectFunc = const QtPromise::QPromiseReject<HttpDataPtr> &;

Q_DECLARE_METATYPE(QRegularExpressionMatch);


#endif

