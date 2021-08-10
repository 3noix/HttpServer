#ifndef HTTP_SERVER_HTTP_REQUEST_HANDLER_H
#define HTTP_SERVER_HTTP_REQUEST_HANDLER_H


#include <QtPromise>

#include "const.h"
#include "HttpData.h"
#include "HttpRequest.h"
#include "HttpResponse.h"


class HTTPSERVER_EXPORT HttpRequestHandler : public QObject
{
	Q_OBJECT

	public:
		HttpRequestHandler(QObject *parent = nullptr) : QObject{parent} {};
		HttpRequestHandler(const HttpRequestHandler &other) = delete;
		HttpRequestHandler(HttpRequestHandler &&other) = delete;
		HttpRequestHandler& operator=(const HttpRequestHandler &other) = delete;
		HttpRequestHandler& operator=(HttpRequestHandler &&other) = delete;
		~HttpRequestHandler() = default;

		virtual HttpPromise handle(HttpDataPtr data) = 0;
};


#endif

