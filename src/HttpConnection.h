#ifndef HTTP_SERVER_HTTP_CONNECTION_H
#define HTTP_SERVER_HTTP_CONNECTION_H


#include "HttpData.h"
#include "HttpServerConfig.h"
#include "HttpRequest.h"
#include "HttpRequestHandler.h"
#include "HttpResponse.h"
#include "util.h"

#include <exception>
#include <list>
#include <memory>
#include <QTcpSocket>
#include <QThread>
#include <QSslConfiguration>
#include <QTimer>
#include <QtPromise>
#include <queue>
#include <unordered_map>


class HTTPSERVER_EXPORT HttpConnection : public QObject
{
	Q_OBJECT

	public:
		HttpConnection(HttpServerConfig *config, HttpRequestHandler *requestHandler, qintptr socketDescriptor,
			QSslConfiguration *sslConfig = nullptr, QObject *parent = nullptr);
		HttpConnection(const HttpConnection &other) = delete;
		HttpConnection(HttpConnection &&other) = delete;
		HttpConnection& operator=(const HttpConnection &other) = delete;
		HttpConnection& operator=(HttpConnection &&other) = delete;
		~HttpConnection();


	private slots:
		void read();
		void bytesWritten(qint64 bytes);
		void timeout();
		void socketDisconnected();
		void sslErrors(const QList<QSslError> &errors);


	signals:
		void disconnected();


	private:
		HttpServerConfig *config = nullptr;
		QTcpSocket *socket = nullptr;
		QHostAddress address;
		QTimer *timeoutTimer = nullptr;
		bool keepAliveMode = false;

		HttpRequest *currentRequest = nullptr;
		HttpResponse *currentResponse = nullptr;
		HttpRequestHandler *requestHandler = nullptr;

		// Responses are stored in a queue to support HTTP pipelining and sending multiple responses
		std::queue<HttpResponse*> pendingResponses;
		// Store data for each request to enable asynchronous logic
		std::unordered_map<HttpResponse*, HttpDataPtr> data;

		const QSslConfiguration *sslConfig;

		void createSocket(qintptr socketDescriptor);
};


#endif

